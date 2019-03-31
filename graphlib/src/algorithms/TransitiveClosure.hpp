#ifndef GL_TRANSITIVE_CLOSURE_HPP
#define GL_TRANSITIVE_CLOSURE_HPP

#include "../structures/Graph.hpp"

namespace gl {

namespace algorithm {
  /**
   * @brief Implements an algorithm that finds the (reachability based) transitive closure of a node
   * @param graph The graph that will be searched
   * @param node The node whose transitive closure we want to find
   */
  template <class GRAPH>
  typename GRAPH::idx_list_t transitiveClosure (const GRAPH& graph, const typename GRAPH::idx_t node) {
    typename GRAPH::idx_list_t out;      // result & temporary node lists
    typename GRAPH::queue_t queue; // nodes to check the neighbours of
    typename GRAPH::visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
    auto v = node;


    // finding closure
    queue.push(v);
    visited[v] = true;
    while(queue.size() != 0) {
      queue.pop();
      out = graph.getUnvisitedNeighbours(v,visited);
      for (auto v : out) {
        visited[v] = true;
        queue.push(v);
      }
      v = queue.top();
    }

    // fill out list with visited nodes
    out.clear();
    for(typename GRAPH::idx_t i = 0; i < graph.numNodes(); ++i) {
      if (visited[i]) {
        out.push_back(i);
      }
    }    
    return out;
  }

} /* Namespace algorithm */
} /* Namespace gl */

#endif /* GL_TRANSITIVE_CLOSURE_HPP */