#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src:test/wrap
echo "LD_PRELOAD=$PWD/test/wrap/libwrap.so ./test/UT"
export LD_PRELOAD=$PWD/test/wrap/libwrap.so
./test/UT
