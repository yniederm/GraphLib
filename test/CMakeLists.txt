cmake_minimum_required(VERSION 3.10)

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
    ConstructFromDegSeq
    Conversion
    CycleDetection
    DegreeSequence
    Dijkstra
    FloydWarshall
    GraphicSequence
    IOTikz
    Kruskal
    Laplacian
    ListGraph
    MathGL
    MathGLColors
    MathGLPlacing
    MatrixGraph
    ReadYAML
    StreamOverload
    TransitiveClosure
    Traversal
    UpdateFlaggedEntities
    )

set(EXTERNAL_TESTS
    IOTikz
    Laplacian
    MathGL
    MathGLColors
    MathGLPlacing
    ReadYAML
    UpdateFlaggedEntities
    Traversal
    )

foreach(TEST_NAME ${TESTS})
  add_executable(${TEST_NAME} Test_${TEST_NAME}.cpp)
  add_test(${TEST_NAME} ${TEST_NAME})
endforeach()


# Add external libraries to the tests that require them
# currently using BLAS and MathGL
find_package(BLAS REQUIRED)
find_package(MathGL)
if(NOT BLAS_FOUND)
  message("BLAS package path not found.")
endif()
message("-- Blas library path: " ${BLAS_LIBRARIES})
if(NOT MathGL_INCLUDE_DIRS)
  message("MathGL package path not found.")
endif(NOT MathGL_INCLUDE_DIRS)

if(BLAS_FOUND)
  if(MathGL_INCLUDE_DIRS)
    foreach(TEST_NAME ${EXTERNAL_TESTS})
      target_link_libraries(${TEST_NAME} ${MathGL_LIBRARIES} ${BLAS_LIBRARIES})
    endforeach()
  endif()
endif()