cmake_minimum_required(VERSION 3.10)

# libraries
add_library(GL SHARED Graph.hpp MatrixGraph.hpp ListGraph.hpp)
set_target_properties(GL PROPERTIES LINKER_LANGUAGE CXX)
