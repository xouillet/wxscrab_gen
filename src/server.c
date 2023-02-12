#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#ifndef PORT
#define PORT 1964
#endif

static enum MHD_Result
answer_to_connection(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method, const char *version,
                     const char *upload_data, size_t *upload_data_size,
                     void **con_cls) {
  const char *page = "<html><body>Hello, browser!</body></html>";
  struct MHD_Response *response;
  enum MHD_Result ret;
  (void)cls;              /* Unused. Silent compiler warning. */
  (void)url;              /* Unused. Silent compiler warning. */
  (void)method;           /* Unused. Silent compiler warning. */
  (void)version;          /* Unused. Silent compiler warning. */
  (void)upload_data;      /* Unused. Silent compiler warning. */
  (void)upload_data_size; /* Unused. Silent compiler warning. */
  (void)con_cls;          /* Unused. Silent compiler warning. */

  response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                             MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

int main(void) {
  struct MHD_Daemon *daemon;

  daemon =
      MHD_start_daemon(MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD, PORT,
                       NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon) {
    return 1;
  }

  printf("Scrabble server started on port %d. Press any key to stop.\n", PORT);
  (void)getchar();

  MHD_stop_daemon(daemon);
  return 0;
}
