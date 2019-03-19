cmake_minimum_required(VERSION 3.1)

add_library(AdjacencyList SHARED AdjacencyList.hpp)
set_target_properties(AdjacencyList PROPERTIES LINKER_LANGUAGE CXX)