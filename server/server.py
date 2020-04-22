#!/usr/bin/env python3

import bottle
from bottle import route, run, template, static_file, response, abort
import xml.etree.cElementTree as ET
import random
import subprocess

app = application = bottle.Bottle()
data = {}

@app.route("/gen_part/<dico>")
def gen_part(dico):
    r = random.SystemRandom()
    pgm = "../gen/gen_part"
    num = r.randrange(0,2**32)
    seed = r.randrange(0,2**16)
    p = subprocess.Popen([pgm, "-d", f"../gen/{dico}.dico", "-n", str(num), "-s", str(seed)], stdout=subprocess.PIPE)
    result = p.communicate()[0]
    response.content_type = 'text/xml'
    return result

if __name__ == '__main__':
    run(app, host='0.0.0.0', port=8080)
