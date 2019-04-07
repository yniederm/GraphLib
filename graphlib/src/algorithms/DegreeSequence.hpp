#ifndef GL_DEGREE_SEQUENCE_HPP
#define GL_DEGREE_SEQUENCE_HPP

#include "../structures/Graph.hpp"
#include "Degrees.hpp"

namespace gl {
namespace algorithm {

/**
 * @brief Computes the out-degree of all nodes in an undirected graph.
 * The resulting list is sorted by descending degree.
 * @param graph The graph to run the algorithm on
 * @return Sorted idx_list_t of all node degrees in the graph.
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