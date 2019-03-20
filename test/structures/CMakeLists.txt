cmake_minimum_required(VERSION 3.10)

# tests
add_executable(TestMGraph Test_MatrixGraph.cpp)
target_link_libraries(TestMGraph GL)
add_test(NAME MGraph_test COMMAND TestMGraph)

add_executable(TestLGraph Test_ListGraph.cpp)
target_link_libraries(TestLGraph GL)
add_test(NAME LGraph_test COMMAND TestLGraph)

add_executable(TestConversion Test_conversion.cpp)
target_link_libraries(TestConversion GL)
add_test(NAME Conversion_test COMMAND TestConversion)