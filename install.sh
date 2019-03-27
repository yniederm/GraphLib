
mkdir build
set -e
cd build
cmake ..
make
echo "Success. Run tests with:"
echo "./build/test/<test-name>"