#ifndef GL_BFS_HPP
#define GL_BFS_HPP

#include <limits>

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/**
 * @class BFS
 * @brief Class that provides Graph traversal using the BFS scheme.
 */

template <class Graph>
class BFS {
  using idx_t = typename Graph::idx_t;                   ///< @brief Type of indices
  using ordered_list_t = typename Graph::ordered_list_t; ///< @brief Ordered node ID list.
  using visit_list_t = typename Graph::visit_list_t;     ///< @brief Boolean list that stored previously visited nodes.
  using BFS_queue_t = std::deque<idx_t>;                 ///< @brief Data structure for BFS searches.
  using distance_list_t = std::vector<idx_t>;            ///< @brief Stores BFS distances of each node.
  using idx_list_t = typename Graph::idx_list_t;         ///< @brief Unordered node ID list.

public: 
  /**
   * Directly computes the BFS algorithm on the specified graph
   * @brief Computation constructor.
   * @param[in] graph Graph that will be traversed
   * @param[in] src Source node. Starting point of the Breadth First Search.
   */
  explicit BFS(const Graph&, const idx_t);

  BFS();                                 ///< Default constructor
  BFS(const BFS &) = default;            ///< Copy constructor
  BFS(BFS &&) noexcept = default;        ///< Move constructor
  BFS &operator=(const BFS &) = default; ///< Copy assignment
  BFS &operator=(BFS &&) = default;      ///< Move assignment
  ~BFS() = default;                      ///< Default destructor

  /**
   * @brief Computation. This is where the BFS algorithm is performed.
   * @param[in] graph Input graph on which the BFS will be computed.
   * @param[in] src source node of BFS.
   */
  void compute(const Graph& graph, const idx_t src);
  /**
   * @brief Computes the BFS node traversal order from the source.
   * @return ordered BFS traversal order
   */
  ordered_list_t getTraversalOrder () const;
  /**
   * @brief Computes the BFS node traversal order from the source.
   * @param[in] distance Maximum distance to source of the nodes that are to be found.
   * @return ordered BFS traversal order up to given distance from source
   */
  ordered_list_t getTraversalOrderMaxDistance (const idx_t& distance) const;

  /**
   * @brief Computes all nodes that are at the exact distance given from the source.
   * @param[in] distance Exact distance to source of the nodes that are to be found.
   * @return list of nodes at exact given distance from source.
   */
  idx_list_t getNodesExactDistance (const idx_t& distance) const;
  /**
   * @brief Returns the number of edges between 'src' and 'dest'.
   * @param[in] dest Node whose BFS distance is to be computed.
   * @return Number of edges between 'src' and 'dest'.
   */
  idx_t getNodeDistance (const idx_t& dest) const;
  /**
   * @brief Computes all nodes that are at within a maximum distance given from the source.
   * @param[in] distance Maximum distance to source of the nodes that are to be found.
   * @return list of nodes within given distance from source.
   */
  idx_list_t getNodesMaxDistance (const idx_t& distance) const;
  /**
   * @brief Computes the BFS shortest path from 'src' to 'dest'.
   * @param[in] dest Destination of the shortest path from 'src'.
   * @return Node indices representing the shortest src-dest-path.
   */
  ordered_list_t getPath (const idx_t& dest) const;

private:
  bool isInitialized_ = false; ///< @brief Boolean storing initialization status
  idx_t src_;                  ///< @brief Source node
  idx_list_t parents_;         ///< @brief Parents on shortest path tree
  ordered_list_t final_;       ///< @brief BFS Traversal order
  distance_list_t distances_;  ///< @brief List containing distances from source
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
BFS<Graph>::BFS() : isInitialized_(false) {}

template <class Graph>
BFS<Graph>::BFS(const Graph& graph, const idx_t src) : isInitialized_(false), src_(src) 
{
  compute(graph, src);
}

template <class Graph>
void BFS<Graph>::compute (const Graph& graph, const idx_t src) 
{
  graph.checkRange(src);
  idx_t INF = std::numeric_limits<idx_t>::max();

  BFS_queue_t queue;      // nodes to check the neighbours of
  ordered_list_t out;     // result node lists
  idx_list_t tempList;    // temporary node lists
  idx_list_t parents(graph.numNodes());  // parents on shortest path tree
  visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
  distance_list_t distances(graph.numNodes(),INF);
  auto v = src;

  // traversal
  queue.push_back(v);
  visited[v] = true;
  distances[v] = 0;
  parents[v] = v;
  while(!queue.empty()) {
    v = queue.front();
    queue.pop_front();
    out.push_back(v);
    tempList = graph.getUnvisitedNeighbours(v,visited);
    for (auto elem : tempList) {
      visited[elem] = true;
      distances[elem] = distances[v] + 1;
      parents[elem] = v;
      queue.push_back(elem);
    }
  }
  parents_ = parents;
  final_ = out;
  distances_ = distances;
  isInitialized_ = true;
}

template <class Graph>
typename Graph::ordered_list_t BFS<Graph>::getTraversalOrder () const {
  GL_ASSERT(isInitialized_,"BFS::getTraversalOrder | BFS has not been initialized with a graph.")
  return final_;
}

template <class Graph>
typename Graph::ordered_list_t BFS<Graph>::getTraversalOrderMaxDistance (const idx_t& distance) const {
  GL_ASSERT(isInitialized_,"BFS::getTraversalOrderMaxDistance | BFS has not been initialized with a graph.")
  ordered_list_t result;
  for (auto x : final_) {
    if (distances_[x] > distance) continue;
    result.push_back(x);
  }
  return result;
}

template <class Graph>
typename Graph::idx_list_t BFS<Graph>::getNodesExactDistance (const idx_t& distance) const {
  GL_ASSERT(isInitialized_,"BFS::getNodesExactDistance | BFS has not been initialized with a graph.")
  idx_list_t result;
  for (auto elem : final_) {
    if (distances_[elem] == distance) result.push_back(elem);
  }
  return result;
}

template <class Graph>
typename Graph::idx_t BFS<Graph>::getNodeDistance (const idx_t& dest) const {
  GL_ASSERT(isInitialized_,"BFS::getNodeDistance | BFS has not been initialized with a graph.")
  GL_ASSERT((0 <= dest), (std::string("Negative index: ") + std::to_string(dest) + std::string(" < 0")))
  GL_ASSERT((dest < distances_.size()), ("Index " + std::to_string(dest) + " is larger than the max: " + std::to_string(distances_.size() - 1)))
  
  return distances_[dest];
}

template <class Graph>
typename Graph::idx_list_t BFS<Graph>::getNodesMaxDistance (const idx_t& distance) const {
  GL_ASSERT(isInitialized_,"BFS::getNodesMaxDistance | BFS has not been initialized with a graph.")
  idx_list_t result;
  for (auto elem : final_) {
    if (distances_[elem] <= distance) result.push_back(elem);
  }
  return result;
}

template <class Graph>
typename Graph::ordered_list_t BFS<Graph>::getPath (const idx_t& dest) const {
  GL_ASSERT(isInitialized_,"BFS::getPath | BFS has not been initialized with a graph.")
  GL_ASSERT((0 <= dest), (std::string("Negative index: ") + std::to_string(dest) + std::string(" < 0")))
  GL_ASSERT((dest < distances_.size()), ("Index " + std::to_string(dest) + " is larger than the max: " + std::to_string(distances_.size() - 1)))
  if (dest == src_) 
  {
    return {src_};
  }
  ordered_list_t result;
  idx_t parent = parents_[dest];
  result.push_front(dest);
  result.push_front(parent);
  while (parent != src_)
  {
    parent = parents_[parent];
    result.push_front(parent);
  }
  return result;
}

} // namespace algorithm
} // namespace gl

#endif // GL_BFS_HPP