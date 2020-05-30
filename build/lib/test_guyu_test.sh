#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/guyu/workarea/gr-guyu/lib
export PATH=/home/guyu/workarea/gr-guyu/build/lib:$PATH
export LD_LIBRARY_PATH=/home/guyu/workarea/gr-guyu/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-guyu 
