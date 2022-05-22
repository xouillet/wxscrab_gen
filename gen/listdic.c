/* Eliot                                                                     */
/* Copyright (C) 1999  antoine.fraboulet                                     */
/* antoine.fraboulet@free.fr                                                 */
/*                                                                           */
/* This program is free software; you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dic_internals.h"
#include "dic.h"

void print_header(Dictionary dic)
{
	printf("Dico information\n");
	printf("root        : %8d\n", dic->root);
	printf("words       : %8d\n", dic->nwords);
	printf("edges       : %8d\n", dic->nedges);
	printf("nodes       : %8d\n", dic->nnodes);
}

void print_dic_hex(Dictionary dic)
{
    printf("%d\n", dic->nedges);
	for (int i = 0; i < dic->nedges + 1; i++) {
	    Dawg_edge* e = dic->dawg + i;
	    printf("%2d ptr=%2d t=%d l=%d f=%d chr=%d (%c)\n",
	        i, e->ptr, e->term, e->last, e->fill, e->chr, e->chr + 'a' - 1);
	}
}

static void
print_dic_list(FILE* out, Dictionary dic, char *buf, char *s, Dawg_edge* i)
{
	if (i->term) {		/* edge points at a complete word */
		*s = '\0';
		fputs(buf, out);
		fputs("\n", out);
	}
	if (i->ptr) {		/* Compute index: is it non-zero ? */
		Dawg_edge* p = dic->dawg + i->ptr;
		do {		/* for each edge out of this node */
			*s = p->chr + 'a' - 1;
			print_dic_list(out, dic, buf, s + 1, p);
		}
		while (!(*p++).last);
	}
}

void usage(char *name)
{
	printf("usage: %s [-a|-d|-h|-l] dictionnaire\n", name);
	printf("  -a : print header\n");
	printf("  -x : print dic in hex\n");
	printf("  -l : print dic word list\n");
}

int main(int argc, char *argv[])
{
	int arg_count;
	int option_print_header = 0;
	int option_print_dic_hex = 0;
	int option_print_dic_list = 0;
	static char buf[80];

	if (argc < 2) {
		usage(argv[0]);
		exit(1);
	}

	arg_count = 1;
	while (argv[arg_count][0] == '-') {
		switch (argv[arg_count][1]) {
		case 'a':
			option_print_header = 1;
			break;
		case 'x':
			option_print_dic_hex = 1;
			break;
		case 'l':
			option_print_dic_list = 1;
			break;
		default:
			usage(argv[0]);
			exit(2);
			break;
		}
		arg_count++;
	}

    Dico dic;
    int ret;
    if ((ret = Dic_init(&dic, argv[arg_count]))) {
        fprintf(stderr, "Dic error %d", ret);
        return ret;
    }

	if (option_print_header) {
		print_header(&dic);
	}
	if (option_print_dic_hex) {
		print_dic_hex(&dic);
	}
	if (option_print_dic_list) {
	    print_dic_list(stdout, &dic, buf, buf, dic.dawg + dic.root);
	}
	return 0;
}
