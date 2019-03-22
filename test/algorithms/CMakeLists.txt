cmake_minimum_required(VERSION 3.10)

# tests
add_executable(TestTransitiveClosure Test_TransitiveClosure.cpp)
target_link_libraries(TestTransitiveClosure GL)
add_test(NAME TransitiveClosure_test COMMAND TestTransitiveClosure)