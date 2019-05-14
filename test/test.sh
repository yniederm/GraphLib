# assumes running from project root directory (../GraphLib)
./install.sh $1
make -C build/ CTEST_OUTPUT_ON_FAILURE=1 test