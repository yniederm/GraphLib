cmake_minimum_required(VERSION 3.10)


# EIGEN library required for this test
# tests
find_package(Eigen3)

if(NOT EIGEN3_INCLUDE_DIR)
  message("Eigen3 package path not found.")
endif(NOT EIGEN3_INCLUDE_DIR)
if(EIGEN3_INCLUDE_DIR)
  include_directories( "${EIGEN3_INCLUDE_DIR}" )
  add_executable(TestIOTikz Test_IOTikz.cpp)
  target_link_libraries(TestIOTikz GL)
  add_test(NAME Tikz_test COMMAND TestIOTikz)
endif()