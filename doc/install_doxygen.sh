# Exit immediately from this script upon error
set -e

# save current directory
dir=$(pwd)
dep_dir=${TRAVIS_BUILD_DIR}/dependencies

mkdir -p ${dep_dir} && cd ${dep_dir}

if [ ! -d "doxygen-1.8.14" ]; then
  wget -O - http://doxygen.nl/files/doxygen-1.8.14.src.tar.gz | tar xz
  cd doxygen-1.8.14
  mkdir build
  cd build
  cmake -Duse_libclang=ON  ..
  make -j2
fi
export PATH=${dep_dir}/doxygen-1.8.14/build/bin:$PATH
doxygen --version

#Change back to where we left off.
cd $dir