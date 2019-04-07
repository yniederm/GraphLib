#ifndef GL_DEGREE_SEQUENCE_HPP
#define GL_DEGREE_SEQUENCE_HPP

#include "../structures/Graph.hpp"
#include "Degrees.hpp"

namespace gl {
namespace algorithm {

/**
 * @brief Traverses the connected component of node using BFS
 * @param graph The graph to run the algorithm on
 */
template <class GRAPH>
typename GRAPH::idx_list_t degreeSequence (const GRAPH& graph) {
  if (!graph.isUndirected()) {
      throw std::logic_error("Graph is not undirected.");
  }
  typename GRAPH::idx_list_t out = gl::algorithm::degrees(graph);
  std::sort(out.begin(), out.end(), std::greater<typename GRAPH::idx_t>());
  return out;
}

} /* namespace algorithm */
} /* namespace gl */

#endif /* GL_DEGREE_SEQUENCE_HPP */