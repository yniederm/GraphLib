#ifndef GL_TEST_HPP
#define GL_TEST_HPP

#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include "../graphlib/src/gl_assert.hpp"

/**
 * @brief Initializes test status variables.
 */
#define GL_TEST_INIT \
int __gl_test_success_count__ = 0; \
int __gl_test_fail_count__ = 0; \
bool __gl_test_except_flag__ = false; \
std::vector<std::string> __gl_test_success__, __gl_test_fail__;

/**
 * @brief Provides a summary of all exectuted tests.
 */
#define GL_TEST_TERM \
std::cout << std::string(15,'-') << " TEST SUMMARY " << std::string(15,'-') << "\n"; \
std::cout << __gl_test_success_count__ + __gl_test_fail_count__ << " tests run.\n"; \
std::cout << "\033[32m Passed Tests (" << __gl_test_success_count__ << ")\033[00m\n"; \
for (auto x : __gl_test_success__) \
{ \
  std::cout << "  " << x << "\n"; \
} \
std::cout << "\033[31m Failed Tests (" << __gl_test_fail_count__ << ")\033[00m\n"; \
for (auto x : __gl_test_fail__) \
{ \
  std::cout << "  " << x << "\n"; \
}

/**
 * @brief Marks the given test as Passed.
 */
#define __GL_TEST_SUCCESS__(TestName) \
++__gl_test_success_count__; \
__gl_test_success__.push_back(TestName); \
std::cout << "\033[32m'" << TestName << "' passed.\033[00m\n";

/**
 * @brief Marks the given test as Failed.
 */
#define __GL_TEST_FAIL__(TestName) \
  ++__gl_test_fail_count__; \
  __gl_test_fail__.push_back(TestName); \
  std::cout << "\033[31m'" << TestName << "' failed.\033[00m\n";


/**
 * @brief Comparison operator that can be used for testing equality.
 * @param Actual Computed result that will be compared to the expected value.
 * @param Expected Expected Value for the computed result.
 * @param TestName A string that can be used as an identifier for which test case is executed.
 */
#define GL_TEST_COMPARE(Actual,Expected,TestName) \
if (Actual == Expected ) \
{ \
  __GL_TEST_SUCCESS__(TestName) \
} \
else \
{ \
  __GL_TEST_FAIL__(TestName) \
}

/**
 * @brief Macro that encapsulates a try/catch block and compares the producederror messages.
 * @param TryBlock Code block that is expected to produce an exception.
 * @param ExpectedError Expected value for the exception message of the try-block.
 * @param TestName A string that can be used as an identifier for which test case is executed.
 */
#define GL_TEST_CATCH_ERROR(TryBlock,ExpectedError,TestName) \
try \
{ \
  TryBlock \
} \
catch(const std::exception& e) \
{ \
  std::cerr << e.what() << '\n'; \
  __gl_test_except_flag__ = true; \
  GL_TEST_COMPARE(std::string(e.what()),ExpectedError,TestName) \
} \
if (!__gl_test_except_flag__) { \
  std::cout << "No exception was thrown when one was expected.\n"; \
  __GL_TEST_FAIL__(TestName) \
} \
__gl_test_except_flag__ = false;

#endif // GL_TEST_HPP