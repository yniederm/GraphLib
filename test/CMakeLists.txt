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

set(BLAS_TESTS
    IOTikz
    Laplacian
    MathGL
    MathGLColors
    ReadYAML
    UpdateFlaggedEntities
    Traversal
    )

set(MATHGL_TESTS
    MathGL
    MathGLColors
    MathGLPlacing
    )

foreach(TEST_NAME ${TESTS})
  add_executable(${TEST_NAME} Test_${TEST_NAME}.cpp)
  add_test(${TEST_NAME} ${TEST_NAME})
endforeach()


# Add the BLAS library to the tests that require it
find_package(BLAS REQUIRED)
if(NOT BLAS_INCLUDE_DIR)
  message("BLAS package path not found.")
endif(NOT BLAS_INCLUDE_DIR)
if(BLAS_INCLUDE_DIR)
  foreach(TEST_NAME ${BLAS_TESTS})
  target_link_libraries(${TEST_NAME} ${BLAS_LIBRARIES})
  endforeach()
endif()

# Add the MathGL library to the tests that require it
find_package(MathGL)
if(NOT MathGL_INCLUDE_DIRS)
  message("MathGL package path not found.")
endif(NOT MathGL_INCLUDE_DIRS)
if(MathGL_INCLUDE_DIRS)
  foreach(TEST_NAME ${MATHGL_TESTS})
    target_link_libraries(${TEST_NAME} ${MathGL_LIBRARIES})
  endforeach()
endif()
