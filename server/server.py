#!/usr/bin/env python3

import bottle
from bottle import route, response

import xml.etree.cElementTree as ET
import random
import subprocess

app = application = bottle.Bottle()

@app.route("/gen_part/<dico>")
@app.route("/gen_part/<dico>/<minpoint:int>")
@app.route("/gen_part/<dico>/<minpoint:int>/<mintour:int>/<maxtour:int>")
def gen_part(dico, minpoint=None, mintour=None, maxtour=None):
    minpoint = 800 if minpoint is None else int(minpoint)
    mintour = 15 if mintour is None else int(mintour)
    maxtour = 30 if maxtour is None else int(maxtour)
    maxtry = 100
    r = random.SystemRandom()
    pgm = "../gen/gen_part"
    n = 0
    while n < maxtry :
        num = r.randrange(0,2**32)
        seed = r.randrange(0,2**16)
        print(num, seed)
        p = subprocess.Popen([pgm, "-d", f"../gen/{dico}.dico", "-n", str(num), "-s", str(seed)], stdout=subprocess.PIPE)
        result = p.communicate()[0]
        tree = ET.fromstring(result)
        tot = int(tree.find("resume/total").text)
        nbtour = int(tree.find("resume/nbtour").text)
        if tot >= minpoint and mintour <= nbtour <= maxtour :
            break
        n += 1

    if n >= maxtry:
        result = """<?xml version="1.0"?><partie></partie>"""

    response.content_type = 'text/xml'
    return result

if __name__ == '__main__':
    bottle.run(app, host='0.0.0.0', port=1964)
