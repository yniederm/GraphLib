#ifndef GL_DIJKSTRA_HPP
#define GL_DIJKSTRA_HPP

#include "../gl_base.hpp"

#include <queue>

namespace gl::algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** 
 * @class Dijkstra
 * @brief Class that computes Dijkstra's Shortest Paths algorithm.
 */

template <class Graph>
class Dijkstra {
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using pair_t = std::pair<val_t,idx_t>;
  using result_t = std::vector<pair_t>;

public: 
  /**
   * @brief Constructor. This is where the shortest distances and the predecessors of each node on the shortest path tree get computed.
   * @param graph Input graph on which the shortest paths will be computed.
   * @param src Source node. All shortest paths will be computed from here.
   */
  Dijkstra(const Graph&, const idx_t);

  Dijkstra() = delete;
  Dijkstra(const Dijkstra &) = default;                ///< @brief Copy constructor
  Dijkstra(Dijkstra &&) noexcept = default;            ///< @brief Move constructor
  Dijkstra &operator=(const Dijkstra &) = default;     ///< @brief Copy assignment
  Dijkstra &operator=(Dijkstra &&) noexcept = default; ///< @brief Move assignment
  ~Dijkstra();   

  /**
   * @brief Provides a Selector Object to color the edges in the Shortest Path Tree.
   * @param[in] color New color for the SPT edges.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t src, const idx_t dest)> EdgeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Provides a Selector Object to color the nodes in the Shortest Path Tree.
   * @param[in] color New color for the SPT nodes.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t node)> NodeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Computes the shortest path length from src to dest.
   * @param dest Node whose distance to src we want to know.
   * @return shortest path length / weight.
   */
  val_t pathLength(const idx_t) const;
  /**
   * @brief Computes the node sequence that represents the shortest path from src to dest.
   * @param dest Node whose shortest path to src we want to know.
   * @return shortest path in form of an ordered list of node indices.
   */
  typename Graph::idx_list_t getPath(const idx_t) const;

private:
  Graph const& graph_; ///< @brief Reference to graph
  Graph result_;       ///< @brief SPT graph
  idx_t src_;          ///< @brief Source node
  result_t final_;     ///< @brief Shortest Path lengths & predecessors
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
Dijkstra<Graph>::~Dijkstra() {}

template <class Graph>
Dijkstra<Graph>::Dijkstra(const Graph& graph, const idx_t src) : graph_(graph), src_(src) {
  graph.checkRange(src);

  // verify that all non-self-loop edge weights are positive
  for (auto it = graph.edge_cbegin(); it != graph.edge_cend(); ++it) {
    if (it->source() != it->dest()) {
      GL_ASSERT(it->weight() > 0, "Found non-positive edge weights in the graph.");
    }
  }

  // priority queue sorting (possibly non-trivial due to usage of idx_t)
  class prio {
    public:
      bool operator() (pair_t& lhs, pair_t& rhs) {
        return lhs.first > rhs.first;
      }
  };

  std::priority_queue<pair_t,std::vector<pair_t>,prio> pq;
  pair_t emptyPair (GL_INF(val_t), GL_INF(val_t));
  typename Graph::visit_list_t visited (graph.numNodes());
  std::vector<pair_t> out (graph.numNodes(),emptyPair);

  pq.push(std::make_pair(0,src));
  out[src] = std::make_pair(src, idx_t(0));

  while (!pq.empty()) {
    idx_t u = pq.top().second;
    pq.pop();
    if(visited[u]) continue;
    visited[u] = true;
    auto neighbours = graph.getUnvisitedNeighbourWeights(u,visited);
    for (const auto& x : neighbours) {
      idx_t v = x.first;
      val_t weight = x.second;
      if(out[v].first > out[u].first + weight) {
        out[v] = std::make_pair(out[u].first + weight,u);
        pq.push(std::make_pair(out[v].first, v));
      }
    }
  }
  final_ = out;

  Graph result(graph.numNodes(),std::string(std::string("SPT of node ")+std::to_string(src)+std::string(" in ")+graph.getGraphLabel()));
  for (idx_t i = 0; i < graph.numNodes(); ++i)
  {
    auto path = getPath(i);
    if (path.size() > 0) {
      idx_t i = 0;
      for (idx_t j = i+1; j < path.size(); ++i, ++j)
      {
        if (!result.hasEdge(path[i],path[j])) 
        {
          result.setEdge(path[i],path[j]);
        }
      }
    }
  }

  result_ = result;
}
template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Graph::idx_t src, const typename Graph::idx_t dest)> Dijkstra<Graph>::EdgeSelector (const gl::Color& color) const 
{
  return [&color, this](const idx_t src, const idx_t dest) -> std::pair<bool,gl::Color> {
    if (result_.hasEdge(src,dest)) 
      return {true,color};
    else
      return {false,gl::Color()};
  };
}

template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Dijkstra<Graph>::idx_t node)> Dijkstra<Graph>::NodeSelector (const gl::Color& color) const 
{
  return [&color, this](const idx_t node) -> std::pair<bool,gl::Color> {
    if (pathLength(node) != val_t(-1))
      return {true,color};
    else return {false,gl::Color("white")};
  };
}

template <class Graph>
typename Graph::val_t Dijkstra<Graph>::pathLength (const idx_t dest) const {
  return final_[dest].first!=GL_INF(val_t) ? final_[dest].first : val_t(-1);
}

template <class Graph>
typename Graph::idx_list_t Dijkstra<Graph>::getPath (const idx_t dest) const {
  typename Graph::idx_list_t out;
  if (pathLength(dest) == val_t(-1))
  {
    return {dest};
  }
  idx_t node = dest;
  while (node != src_) {
    out.push_back(node);
    node = final_[node].second;
  }
  out.push_back(src_);
  std::reverse(out.begin(),out.end());
  return out;
}

} // namespace gl::algorithm  

#endif // GL_DIJKSTRA_HPP