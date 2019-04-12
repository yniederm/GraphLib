#ifndef GL_STREAM_OVERLOAD_HPP
#define GL_STREAM_OVERLOAD_HPP

#include "../structures/Graph.hpp"

/**
 * @name Prints all contents of the given GraphLib container.
 * @param os Stream that will be used for output
 * @param rhs Graph that will be printed
 */
//@{
/**
 * @brief Prints all edges in the format start--weight->end & total edge number.
 */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
std::ostream& operator<< (std::ostream& os, const gl::Graph<SCALAR, STORAGE_KIND, DIRECTION>& rhs) {
  using idx_t = typename gl::Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t;
  idx_t counter = 0;
  for(idx_t start = 0; start < rhs.numNodes(); start++)
  {
    auto neighbours = rhs.getNeighbourWeights(start);
    for(const auto& edge : neighbours)
    {
      os << start << "--" << edge.second << "->" << edge.first << std::endl;
      ++counter;
    }
  }
  os << "Total Edges: " << counter << std::endl;
  return os;
}

/**
 * @brief Prints all elements of an std::list.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::list<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs)
    os << it << " ";
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::vector.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::vector<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs)
    os << it << " ";
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::deque.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::deque<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs) {
    os << it << " ";
  }

  os << "]\n";
  return os;
}

/**
 * Only supports copying the stack, due to its implementation.
 * @brief Prints all elements of an std::stack.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, std::stack<idx_t> rhs) {
  os << "[ ";
  while (!rhs.empty()) { 
    os << rhs.top() << " "; 
    rhs.pop(); 
  } 

  os << "]\n";
  return os;
}
//@}

#endif /* GL_STREAM_OVERLOAD_HPP */