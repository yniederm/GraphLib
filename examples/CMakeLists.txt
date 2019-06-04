cmake_minimum_required(VERSION 3.1...3.14 FATAL_ERROR)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

link_directories(
  ${PROJECT_BINARY_DIR}/graphlib
)

set(EXAMPLES
    SwitzerlandDijkstra
    ColoredDijkstraKruskal
    IOTikz
    MathGL
    MathGLColors
    MathGLPlacing
    YAMLReader
)

set(EXTERNAL_EXAMPLES
    ColoredDijkstraKruskal
    IOTikz
    MathGL
    MathGLColors
    MathGLPlacing
    YAMLReader
)

foreach(EXAMPLE_NAME ${EXAMPLES})
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
endforeach()

if(LAPACK_FOUND AND BLAS_FOUND AND MathGL_FOUND)
  foreach(EXAMPLE_NAME ${EXTERNAL_EXAMPLES})
    target_link_libraries(${EXAMPLE_NAME} ${MathGL_LIBRARIES} ${LAPACKBLAS_LIBRARIES})
  endforeach()
endif()