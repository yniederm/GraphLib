cmake_minimum_required(VERSION 3.10)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

link_directories(
  ${PROJECT_BINARY_DIR}/graphlib
)

set(TESTS
    Color
    Conversion
    CycleDetection
    DegreeSequence
    Dijkstra
    IOTikz
    ListGraph
    MathGL
    MathGLColors
    MathGLPlacing
    MatrixGraph
    PrintContainer
    TransitiveClosure
    Traversal
    )

set(EIGEN_TESTS
    IOTikz
    MathGL
    MathGLColors
    )

set(MATHGL_TESTS
    MathGL
    MathGLColors
    MathGLPlacing)

foreach(TEST_NAME ${TESTS})
  add_executable(${TEST_NAME} Test_${TEST_NAME}.cpp)
  add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

# Add the Eigen library to the tests that require it
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
if(NOT EIGEN3_INCLUDE_DIR)
  message("Eigen3 package path not found.")
endif(NOT EIGEN3_INCLUDE_DIR)
if(EIGEN3_INCLUDE_DIR)
  foreach(TEST_NAME ${EIGEN_TESTS})
  target_link_libraries(${TEST_NAME} Eigen3::Eigen)
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
