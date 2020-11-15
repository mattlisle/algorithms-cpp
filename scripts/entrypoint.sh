#!/usr/bin/env bash

set -e

WORKDIR=$(pwd)

mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build .
python3 ../scripts/run-clang-tidy.py -p $WORKDIR/build files $WORKDIR/src $WORKDIR/test
ctest

