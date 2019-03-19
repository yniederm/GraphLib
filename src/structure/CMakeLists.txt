cmake_minimum_required(VERSION 3.10)

# libraries
add_library(AdjacencyMatrix SHARED AdjacencyMatrix.hpp)
set_target_properties(AdjacencyMatrix PROPERTIES LINKER_LANGUAGE CXX)

add_library(AdjacencyList SHARED AdjacencyList.hpp)
set_target_properties(AdjacencyList PROPERTIES LINKER_LANGUAGE CXX)


# tests
add_executable(AdjacencyMatrixTest AdjacencyMatrix_main.cpp)
target_link_libraries(AdjacencyMatrixTest AdjacencyMatrix)
add_test(NAME AdjacencyMatrix_functions COMMAND AdjacencyMatrixTest)
