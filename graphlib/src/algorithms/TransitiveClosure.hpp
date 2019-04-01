#ifndef GL_TRANSITIVE_CLOSURE_HPP
#define GL_TRANSITIVE_CLOSURE_HPP

#include "../structures/Graph.hpp"
#include "DFS.hpp"

namespace gl {
namespace algorithm {

  /**
   * @brief Implements an algorithm that finds the (reachability based) transitive closure of a node
   * @param graph The graph that will be searched
   * @param node The node whose transitive closure we want to find
   */
  template <class GRAPH>
  typename GRAPH::ordered_list_t transitiveClosure (const GRAPH& graph, const typename GRAPH::idx_t node) {
    typename GRAPH::visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
    typename GRAPH::ordered_list_t out;
    out = gl::algorithm::DFS_recursive(graph, node, visited, out);
    out.clear();
    // fill out list with visited nodes
    for(typename GRAPH::idx_t i = 0; i < graph.numNodes(); ++i) {
      if (visited[i]) {
        out.emplace_back(i);
      }
    }    
    return out;
  }

} /* namespace algorithm */
} /* namespace gl */

#endif /* GL_TRANSITIVE_CLOSURE_HPP */