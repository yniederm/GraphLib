cmake_minimum_required(VERSION 3.1...3.14 FATAL_ERROR)
project(GraphLibrary)
set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Check that this is not an in-source build:
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(SEND_ERROR "In-source builds are not allowed.")
endif()

# Documentation build by default ON
option(BUILD_DOC "Build documentation" ON)
if(BUILD_DOC)
  # Run doxygen
  add_subdirectory(doc)
endif()

# Example build by default ON
option(BUILD_EXAMPLES "Build examples" ON)
# Unit test build by default ON
option(ENABLE_TESTING "Build unit tests" ON)

if (BUILD_EXAMPLES OR ENABLE_TESTING)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
  message(STATUS ${CMAKE_MODULE_PATH})
  # Add external libraries to the exectuables that require them
  # currently using BLAS and MathGL
  find_package(BLAS)
  find_package(LAPACK)
  if(LAPACK_FOUND AND BLAS_FOUND)
    set(LAPACKBLAS_LIBRARIES ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
  endif()
  find_package(MathGL)

  if(NOT LAPACK_FOUND)
    message("BLAS package path not found.")
  endif(NOT LAPACK_FOUND)

  if(NOT BLAS_FOUND)
    message("BLAS package path not found.")
  endif(NOT BLAS_FOUND)

  if(NOT MathGL_INCLUDE_DIRS)
    message("MathGL package path not found.")
  endif(NOT MathGL_INCLUDE_DIRS)
endif()

if(BUILD_EXAMPLES)
  # Build examples
  add_subdirectory(examples)
endif()

if(ENABLE_TESTING) 
  # Enable testing
  enable_testing()
  add_subdirectory(test)
endif()

# set release build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(graphlib)

