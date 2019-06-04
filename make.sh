#!/usr/bin/env bash

mkdir -p build
set -e
cd build
cmake ..
make $1
echo "Success. Run tests with:"
echo "./test/test.sh"