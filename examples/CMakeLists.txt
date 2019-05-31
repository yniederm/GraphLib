cmake_minimum_required(VERSION 3.10)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

link_directories(
  ${PROJECT_BINARY_DIR}/graphlib
)

set(EXAMPLES
    SwitzerlandDijkstra
    )

#set (EXTERNAL_EXAMPLES
#
#)

foreach(EXAMPLE_NAME ${EXAMPLES})
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
endforeach()


#find_package(BLAS REQUIRED)
#find_package(MathGL)
#if(NOT BLAS_INCLUDE_DIR)
#  message("BLAS package path not found.")
#endif(NOT BLAS_INCLUDE_DIR)

#if(NOT MathGL_INCLUDE_DIRS)
#  message("MathGL package path not found.")
#endif(NOT MathGL_INCLUDE_DIRS)

#if(BLAS_INCLUDE_DIR)
#  if(MathGL_INCLUDE_DIRS)
#    foreach(TEST_NAME ${EXTERNAL_TESTS})
#      target_link_libraries(${TEST_NAME} ${BLAS_LIBRARIES} ${MathGL_LIBRARIES})
#    endforeach()
#  endif()
#endif()

