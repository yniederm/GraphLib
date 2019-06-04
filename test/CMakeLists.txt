cmake_minimum_required(VERSION 3.1...3.14 FATAL_ERROR)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

link_directories(
  ${PROJECT_BINARY_DIR}/graphlib
)

set(TESTS
    Centrality
    Color
    CycleDetection
    DegreeSequence
    Dijkstra
    DisjointSets
    Edge
    FloydWarshall
    GraphBase
    GraphConstructor
    GraphicSequence
    GraphInterface
    Kruskal
    Laplacian
    Node
    Property
    StreamOverload
    TransitiveClosure
    Traversal
)

set(EXTERNAL_TESTS
    Laplacian
)

foreach(TEST_NAME ${TESTS})
  add_executable(${TEST_NAME} Test_${TEST_NAME}.cpp)
  add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

if(LAPACK_FOUND AND BLAS_FOUND AND MathGL_FOUND)
  foreach(TEST_NAME ${EXTERNAL_TESTS})
    target_link_libraries(${TEST_NAME} ${MathGL_LIBRARIES} ${LAPACKBLAS_LIBRARIES})
  endforeach()
endif()