#ifndef GL_TRANSITIVE_CLOSURE_HPP
#define GL_TRANSITIVE_CLOSURE_HPP

#include "../structures/Graph.hpp"

namespace gl
{
  /**
   * @brief Implements an algorithm that finds the (reachability based) transitive closure of a node
   * @param node The node whose transitive closure we want to find
   */
  template <class SCALAR>
  typename Graph<SCALAR>::idx_list_t Graph<SCALAR>::transitiveClosure (const typename Graph<SCALAR>::idx_t node) const {
    idx_list_t out;      // result & temporary node lists
    queue_t queue; // nodes to check the neighbours of
    visit_list_t visited(numNodes(),false);  // list of visited nodes
    idx_t v = node;

    // finding closure
    queue.push(v);
    visited[v] = true;
    while(queue.size() != 0) {
      queue.pop();
      out = getUnvisitedNeighbours(v,visited);
      for (auto v : out) {
        visited[v] = true;
        queue.push(v);
      }
      v = queue.top();
    }

    // fill out list with visited nodes
    out.clear();
    for(idx_t i = 0; i < numNodes(); ++i) {
      if (visited[i]) {
        out.push_back(i);
      }
    }    
    return out;
  }

} /* Namespace gl */

#endif /* GL_TRANSITIVE_CLOSURE_HPP */