#ifndef GL_ASSERT_HPP

#include <stdexcept>
#include <string>

#ifdef NDEBUG
#define GL_ASSERT(EXPR_ERROR_MSG) ((void)0)
#else
  /**
   * @brief Custom assert that supports attaching a message.
   * @param EXPR If this evaluates to false, the assertion is triggered.
   * @param ERROR_MSG String that will contain info on the error.
   */
#define GL_ASSERT(EXPR,ERROR_MSG) \
if (!(EXPR)) { \
  std::string errorMessage (ERROR_MSG); \
  throw std::runtime_error(errorMessage); \
} 
#endif

#endif // GL_ASSERT_HPP


