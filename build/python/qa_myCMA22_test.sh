#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/guyu/workarea/gr-guyu/python
export PATH=/home/guyu/workarea/gr-guyu/build/python:$PATH
export LD_LIBRARY_PATH=/home/guyu/workarea/gr-guyu/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/guyu/workarea/gr-guyu/build/swig:$PYTHONPATH
/usr/bin/python2 /home/guyu/workarea/gr-guyu/python/qa_myCMA22.py 
