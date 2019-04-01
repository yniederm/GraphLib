#ifndef GL_BFS_HPP
#define GL_BFS_HPP

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

  /**
   * @brief Traverses the connected component of node using BFS
   * @param graph The graph to run the algorithm on
   * @param node Start point of the graph search
   */
  template <class GRAPH>
  typename GRAPH::ordered_list_t BFS (const GRAPH& graph, const typename GRAPH::idx_t node) {
    typename GRAPH::ordered_list_t out;     // result node lists
    typename GRAPH::idx_list_t tempList;    // temporary node lists
    typename GRAPH::BFS_queue_t queue;      // nodes to check the neighbours of
    typename GRAPH::visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
    auto v = node;

    // traversal
    queue.push(v);
    visited[v] = true;
    while(!queue.empty()) {
      v = queue.front();
      queue.pop();
      out.push_back(v);
      tempList = graph.getUnvisitedNeighbours(v,visited);
      for (auto elem : tempList) {
        visited[elem] = true;
        queue.push(elem);
      }
    }
    return out;
  }

} /* namespace algorithm */
} /* namespace gl */

#endif /* GL_BFS_HPP */