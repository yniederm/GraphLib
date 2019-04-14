#ifndef GL_DIJKSTRA_HPP
#define GL_DIJKSTRA_HPP


#include <queue>
#include <limits>

namespace gl::algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Dijkstra
 @brief Class that computes Dijkstra's Shortest Paths algorithm.
  */

template <class SCALAR, class STORAGE, class DIR>
class Dijkstra {
  using Graph = gl::Graph<SCALAR,STORAGE,DIR>;
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using ordered_list_t = typename Graph::ordered_list_t;
  using pair_t = std::pair<val_t,idx_t>;
  using result_t = std::vector<pair_t>;
  using visit_list_t = typename Graph::visit_list_t;

public: 
  Dijkstra();
  Dijkstra(const Graph&, const idx_t);
  ~Dijkstra();

  val_t pathLength(const idx_t) const;
  ordered_list_t getPath(const idx_t) const;

private:
  Graph const& _graph;
  idx_t _src;
  result_t _final;
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class SCALAR, class STORAGE, class DIR>
Dijkstra<SCALAR,STORAGE,DIR>::Dijkstra() {}

template <class SCALAR, class STORAGE, class DIR>
Dijkstra<SCALAR,STORAGE,DIR>::~Dijkstra() {}

  /**
   * Constructor. This is where the shortest distances and the predecessors of each node on the shortest path tree get computed.
   * @param graph Input graph on which the shortest paths will be computed.
   * @param src Source node. All shortest paths will be computed from here.
   */
template <class SCALAR, class STORAGE, class DIR>
Dijkstra<SCALAR,STORAGE,DIR>::Dijkstra(const Graph& graph, const idx_t src) : _graph(graph), _src(src) {

  class prio {
    public:
      bool operator() (pair_t& lhs, pair_t& rhs) {
        return lhs.first > rhs.first;
      }
  };

  std::priority_queue<pair_t,std::vector<pair_t>,prio> pq;
  val_t INF = std::numeric_limits<val_t>::max();
  pair_t emptyPair (INF, INF);
  visit_list_t visited (graph.numNodes());
  std::vector<pair_t> out (graph.numNodes(),emptyPair);

  pq.push(std::make_pair(0,src));
  out[src] = std::make_pair(src, idx_t(0));

  while (!pq.empty()) {
    idx_t u = pq.top().second;
    pq.pop();
    if(visited[u]) continue;
    visited[u] = true;
    auto neighbours = graph.getUnvisitedEdges(u,visited);
    for (const auto& x : neighbours) {
      idx_t v = x.first;
      val_t weight = x.second;
      if(out[v].first > out[u].first + weight) {
        out[v] = std::make_pair(out[u].first + weight,u);
        pq.push(std::make_pair(out[v].first, v));
      }
    }
  }
  _final = out;
}

  /**
   * @brief Computes the shortest path length from src to dest.
   * @param dest Node whose distance to src we want to know.
   * @return shortest path length / weight.
   */
template <class SCALAR, class STORAGE, class DIR>
typename gl::Graph<SCALAR,STORAGE,DIR>::val_t Dijkstra<SCALAR,STORAGE,DIR>::pathLength (const idx_t dest) const {
  return _final[dest].first!=std::numeric_limits<val_t>::max() ? _final[dest].first : val_t(-1);
}

  /**
   * @brief Computes the node sequence that represents the shortest path from src to dest.
   * @param dest Node whose shortest path to src we want to know.
   * @return shortest path in form of an ordered list of node indices.
   */
template <class SCALAR, class STORAGE, class DIR>
typename gl::Graph<SCALAR,STORAGE,DIR>::ordered_list_t Dijkstra<SCALAR,STORAGE,DIR>::getPath (const idx_t dest) const {
  typename gl::Graph<SCALAR,STORAGE,DIR>::ordered_list_t out;
  idx_t node = dest;
  while (node != _src) {
    out.push_front(node);
    node = _final[node].second;
  }
  out.push_front(_src);
  return out;
}

} // namespace gl::algorithm  

#endif // GL_DIJKSTRA_HPP