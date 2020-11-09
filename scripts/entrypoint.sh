#!/usr/bin/env bash

set -e

WORKDIR=$(pwd)

mkdir -p build
cd build
cmake ..
cmake --build .
python3 ../scripts/run-clang-tidy.py files $WORKDIR/src $WORKDIR/test
ctest

