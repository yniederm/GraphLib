
mkdir -p build
set -e
cd build
cmake ..
make $1
echo "Success. Run tests with:"
echo "./build/test/<test-name>"