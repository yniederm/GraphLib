# assumes running from project root directory (../GraphLib)
./build.sh
make -C build/ CTEST_OUTPUT_ON_FAILURE=1 test