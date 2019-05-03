#ifndef GL_DEGREES_HPP
#define GL_DEGREES_HPP

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

/**
 * @brief Computes the out-degrees of all nodes in a graph.
 * @param graph The graph to run the algorithm on
 * @tparam Graph Type of graph
 * @return idx_list_t containing the degree of node i at position i
 */
template <class Graph>
typename Graph::idx_list_t degrees (const Graph& graph) {
  typename Graph::idx_list_t out(graph.numNodes());    // degree node list

  for (typename Graph::idx_t node = 0; node < graph.numNodes(); ++node) {
    out[node] = graph.getNodeDegree(node);
  }
  return out;
}

} // namespace algorithm
} // namespace gl

#endif // GL_DEGREES_HPP