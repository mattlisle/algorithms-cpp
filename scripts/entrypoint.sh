#!/usr/bin/env bash

set -e

WORKDIR=$(pwd)


mkdir -p build
cd build

# Build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build .

# Format
find $WORKDIR/src/ $WORKDIR/test/ $WORKDIR/include/algorithms-cpp -name '*.cpp' -o -name '*.hpp' |
  xargs clang-format-9 --output-replacements-xml |
  grep '<replacement ' &&
  echo "There were format violations" &&
  exit 1

# Lint
python3 ../scripts/run-clang-tidy.py -p $WORKDIR/build files $WORKDIR/src $WORKDIR/test $WORKDIR/include/algorithms-cpp

# Test
ctest

