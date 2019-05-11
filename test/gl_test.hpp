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
 * @brief Comparison operator that can be used for testing numerical equality of two container.
 * @param Actual Computed container that will be compared to the expected container.
 * @param Expected Expected Value for the computed result.
 * @param AbsTol Absolute tolerance for numerical error.
 * @param TestName A string that can be used as an identifier for which test case is executed.
 */
#define GL_TEST_NUMERIC_CONTAINER_COMPARE(Actual,Expected,AbsTol) \
GL_ASSERT_EQUAL_DESC(Actual.size(),Expected.size(),"Container sizes") \
auto et = Expected.begin(); \
for (auto at = Actual.begin(); at != Actual.end(); ++at, ++et) \
{ \
  GL_ASSERT_EQUAL_ABSTOL(*at,*et,AbsTol) \
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
  GL_ASSERT_EQUAL(std::string(e.what()),ExpectedError) \
} \
if (!__gl_test_except_flag__) { \
  std::cerr << "No exception was thrown when one was expected.\n"; \
  __GL_TEST_FAIL__(TestName) \
} \
__gl_test_except_flag__ = false;

/**
 * @brief Operator that can be used to assert a condition.
 * @param Condition Predicate that is expected to be true.
 */
#define GL_ASSERT_THROW(Condition)                                \
{                                                                 \
  if( !(Condition) )                                              \
  {                                                               \
    throw std::runtime_error(   std::string(__FILE__)             \
                              + std::string(":")                  \
                              + std::to_string(__LINE__)          \
                              + std::string(" in ")               \
                              + std::string(__PRETTY_FUNCTION__)  \
    );                                                            \
  }                                                               \
}

/**
 * @brief Comparison operator that can be used for testing equality.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 */
#define GL_ASSERT_EQUAL(A,B)                                     \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}

/**
 * @brief Comparison operator that can be used for testing equality.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 * @param Description A string that can be used as an identifier for which comparison is performed.
 */
#define GL_ASSERT_EQUAL_DESC(A,B,Description)                    \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": (")               \
                              + std::string(Description)         \
                              + std::string(") ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}

/**
 * @brief Comparison operator that can be used for testing equality for numerical values.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 * @param AbsTol Absolute tolerance for the difference between the two values.
 */
#define GL_ASSERT_EQUAL_ABSTOL(A,B,AbsTol)                       \
{                                                                \
  if( std::abs(A - B) >= AbsTol )                                \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": (Tolerance: ")    \
                              + std::to_string(AbsTol)           \
                              + std::string(") ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}


#endif // GL_TEST_HPP