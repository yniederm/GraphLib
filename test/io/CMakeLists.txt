cmake_minimum_required(VERSION 3.10)

find_package(MathGL)

# tests
add_executable(TestIOTikz Test_IOTikz.cpp)
add_test(NAME Tikz_test COMMAND TestIOTikz)

add_executable(TestMathGL Test_MathGL.cpp)
target_link_libraries(TestMathGL ${MathGL_LIBRARIES})
add_test(NAME MathGL_test COMMAND TestMathGL)

