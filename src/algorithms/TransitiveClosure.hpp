#ifndef GL_TRANSITIVE_CLOSURE_HPP
#define GL_TRANSITIVE_CLOSURE_HPP

#include "../structures/Graph.hpp"
#include <queue>
#include <bitset>
namespace gl
{
  /**
   * @brief Implements an algorithm that finds the (reachability based) transitive closure of a node
   * @param node The node whose transitive closure we want to find
   */
  template <class SCALAR>
  typename Graph<SCALAR>::idx_list_t Graph<SCALAR>::transitiveClosure (const typename Graph<SCALAR>::idx_t node) const {
    idx_list_t out;
    idx_list_t tempList;
    std::priority_queue<idx_t> queue;
    std::vector<bool> visited(numNodes(),false); 
    idx_t v = node;
    queue.push(v);
    visited[v] = true;
    do{
      queue.pop();
      tempList = getUnvisitedNeighbours(v,visited);
      for (auto v : tempList) {
        visited[v] = true;
        queue.push(v);
      }
      out.insert(
          out.end(),
          std::make_move_iterator(tempList.begin()),
          std::make_move_iterator(tempList.end())
        );
      v = queue.top();
    } while(queue.size() != 0);
    return out;
  }

} /* Namespace gl */

#endif /* GL_TRANSITIVE_CLOSURE_HPP */