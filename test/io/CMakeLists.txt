cmake_minimum_required(VERSION 3.10)

# tests
add_executable(TestIOTikz Test_IOTikz.cpp)
target_link_libraries(TestIOTikz GL)
add_test(NAME Tikz_test COMMAND TestIOTikz)