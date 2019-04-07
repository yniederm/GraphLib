#ifndef GL_DFS_HPP
#define GL_DFS_HPP

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

  /**
   * @brief Recursive call for DFS
   * @param graph The graph to run the algorithm on
   * @param node Start point of the graph search
   * @param visited list keeping track of already visited nodes
   * @param out result list
   */
  template <class GRAPH>
  void DFS_recursive (const GRAPH& graph, const typename GRAPH::idx_t node, typename GRAPH::visit_list_t& visited, typename GRAPH::ordered_list_t& out) {
    typename GRAPH::idx_list_t tempList; // temporary node lists
    typename GRAPH::DFS_queue_t queue; // nodes to check the neighbours of

    visited[node] = true;
    out.emplace_back(node);
    tempList = graph.getUnvisitedNeighbours(node,visited);
    
    for (auto v : tempList) {
      if (!visited[v]) {
        DFS_recursive(graph, v, visited, out);
      }
    }
  }

  /**
   * @brief Traverses the connected component of node using DFS
   * @param graph The graph to run the algorithm on
   * @param node Start point of the graph search
   * @return Sequence of all nodes visited by a DFS run.
   */
  template <class GRAPH>
  typename GRAPH::ordered_list_t DFS (const GRAPH& graph, const typename GRAPH::idx_t node) {
    typename GRAPH::visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
    typename GRAPH::ordered_list_t out;      // result node lists
    DFS_recursive(graph, node, visited, out);
    return out;
  }

} /* namespace algorithm */
} /* namespace gl */

#endif /* GL_DFS_HPP */