#ifndef GL_PRINT_CONTAINER_HPP
#define GL_PRINT_CONTAINER_HPP

#include "../structures/Graph.hpp"
#include "StreamOverload.hpp"

namespace gl {
namespace io {

  /**
   * @name Prints all contents of the given GraphLib container.
   * @param os Stream that will be used for output
   * @param rhs Container that will be printed
   */
  //@{
  /**
   * @brief Unspecialized template to throw errors.
   */
  template <class container> void printContainer(const container& rhs) {
    throw "Invalid container type.";
  } 
  
  /**
   * @brief Prints all elements of an std::list.
   */
  template <class idx_t> void printContainer(const std::list<idx_t>& rhs) {
    std::cout << rhs;
  } 

  /**
   * @brief Prints all elements of an std::vector.
   */
  template <class idx_t> void printContainer(const std::vector<idx_t>& rhs) {
    std::cout << rhs;
  }

  /**
   * @brief Prints all elements of an std::queue.
   */
  template <class idx_t> void printContainer(const std::deque<idx_t>& rhs) {
    std::cout << rhs;
  } 

  /**
   * @brief Prints all elements of an std::stack.
   */
  template <class idx_t> void printContainer(const std::stack<idx_t>& rhs) {
    std::cout << rhs;
  } 
  //@}

} // namespace io
} // namespace gl

#endif // GL_PRINT_CONTAINER_HPP