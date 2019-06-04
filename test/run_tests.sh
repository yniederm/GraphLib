#!/usr/bin/env bash

# assumes running from project root directory (../GraphLib)
make -C build/ CTEST_OUTPUT_ON_FAILURE=1 test