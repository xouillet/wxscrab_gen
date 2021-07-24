#!/bin/sh
cd gen
swig -python dic.i
python3 setup.py install --user
scons
