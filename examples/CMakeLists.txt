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

set(EIGEN_EXAMPLES
    SwitzerlandDijkstra
    )
# set(MATHGL_EXAMPLES
#     MathGL
#     MathGLColors
#     MathGLPlacing
#     )

foreach(EXAMPLE_NAME ${EXAMPLES})
  add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
endforeach()

# Add the Eigen library to the tests that require it
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
if(NOT EIGEN3_INCLUDE_DIR)
  message("Eigen3 package path not found.")
endif(NOT EIGEN3_INCLUDE_DIR)
if(EIGEN3_INCLUDE_DIR)
  foreach(EXAMPLE_NAME ${EIGEN_EXAMPLES})
  target_link_libraries(${EXAMPLE_NAME} Eigen3::Eigen)
  endforeach()
endif()

# Add the MathGL library to the tests that require it
# find_package(MathGL)
# if(NOT MathGL_INCLUDE_DIRS)
#   message("MathGL package path not found.")
# endif(NOT MathGL_INCLUDE_DIRS)
# if(MathGL_INCLUDE_DIRS)
#   foreach(TEST_NAME ${MATHGL_TESTS})
#     target_link_libraries(${TEST_NAME} ${MathGL_LIBRARIES})
#   endforeach()
# endif()
