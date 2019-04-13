#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src:test/wrap
LD_PRELOAD=$PWD/test/wrap/libwrap.so ./test/UT

rm -f ut.info cov_output 2>/dev/null
lcov -c -d src/ --output-file ut.info
genhtml ut.info --output-directory cov_output

