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
  using pair_t = std::pair<Distance<val_t>,idx_t>;
  using result_t = std::vector<pair_t>;

public: 
  /**
   * This constructor takes a graph argument, ready for usage.
   * @brief Initialized Constructor.
   * @param[in] graph Graph that will be traversed
   */
  explicit Dijkstra(const Graph graph);    ///< Constructor with Graph included

  Dijkstra();                                          ///< Default constructor
  Dijkstra(const Dijkstra &) = default;                ///< Copy constructor
  Dijkstra(Dijkstra &&) noexcept = default;            ///< Move constructor
  Dijkstra &operator=(const Dijkstra &) = default;     ///< Copy assignment
  Dijkstra &operator=(Dijkstra &&) noexcept = default; ///< Move assignment
  ~Dijkstra() = default;                               ///< Default destructor

  Distance<val_t> pathLength(const idx_t src, const idx_t dest);
  /**
   * @brief Computes the node sequence that represents the shortest path from src to dest.
   * @param[in] src Start of shortest path
   * @param[in] dest End of shortest path
   * @return shortest path in form of an ordered list of node indices.
   */
  std::pair<bool,typename Graph::idx_list_t> getPath(const idx_t src, const idx_t dest);
  /**
   * @brief Returns a graph that only contains the edges of the SPT (Shortest Path Tree)
   * @param[in] src Node whose SPT is to be known
   * @return SPT Graph.
   */
  Graph getSPT(const idx_t src);
  /**
   * @brief Initializes the algorithm with a new Graph
   * @param[in] graph Graph storing information for the Shortest Path Algorithm
   */
  void initialize(const Graph graph);

private:  

  /**
   * @brief Computation. This is where the shortest distances and the predecessors of each node on the shortest path tree get computed.
   * @param[in] src Source node. All shortest paths will be computed from here.
   */
  void compute(const idx_t src);

  
  bool isInitializedWithGraph_; ///< @brief Boolean indicating whether the class has been initialized with a Graph.
  std::vector<bool> isInitializedWithSource_; ///< @brief Boolean vector indicating whether the node whose ID corresponds to an element in the vector had its shortest path tree computed
  Graph graph_;                   ///< @brief Source Graph
  // TODO: make pointer to prevent copies

  std::vector<Graph> result_;     ///< @brief SPT graph
  std::vector<result_t> final_;   ///< @brief Shortest Path lengths & predecessors
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
Dijkstra<Graph>::Dijkstra() : isInitializedWithGraph_(false),
                              isInitializedWithSource_(1,false) {}

template <class Graph>
Dijkstra<Graph>::Dijkstra(Graph graph) : isInitializedWithGraph_(true),                                         isInitializedWithSource_(graph.numNodes(),false),   
                                         graph_(graph),
                                         result_(graph.numNodes()),
                                         final_(graph.numNodes()) {}

template <class Graph>
void Dijkstra<Graph>::compute(const idx_t src)
{
  // range has been checked in calling functions

  // verify that all non-self-loop edge weights are positive
  for (auto it = graph_.edge_cbegin(); it != graph_.edge_cend(); ++it) {
    if (it->source() != it->dest()) {
      GL_ASSERT(it->weight() > 0, "Dijkstra::compute | Found non-positive edge weights in the graph.");
    }
  }

  // priority queue sorting (possibly non-trivial due to usage of Distance)
  class prio {
    public:
      bool operator() (pair_t& lhs, pair_t& rhs) {
        return lhs.first > rhs.first;
      }
  };

  std::priority_queue<pair_t,std::vector<pair_t>,prio> pq;
  typename Graph::visit_list_t visited (graph_.numNodes());
  std::vector<pair_t> out (graph_.numNodes());

  pq.push(std::make_pair(0,src));
  out[src] = std::make_pair(idx_t(0),src);

  while (!pq.empty()) {
    idx_t u = pq.top().second;
    pq.pop();
    if(visited[u]) continue;
    visited[u] = true;
    auto neighbours = graph_.getUnvisitedNeighbourWeights(u,visited);
    for (const auto& x : neighbours) {
      idx_t v = x.first;
      Distance<val_t> temp_weight (x.second);
      if(out[v].first > out[u].first + temp_weight) {
        out[v] = std::make_pair(out[u].first + temp_weight,u);
        pq.push(std::make_pair(out[v].first, v));
      }
    }
  }
  final_[src] = out;
  isInitializedWithSource_[src] = true;

  Graph result(graph_.numNodes(),std::string(std::string("SPT of node ")+std::to_string(src)+std::string(" in ")+graph_.getGraphLabel()));
  for (idx_t i = 0; i < graph_.numNodes(); ++i)
  {
    auto path = getPath(src, i);
    if (path.first) {
      idx_t i = 0;
      for (idx_t j = i+1; j < path.second.size(); ++i, ++j)
      {
        if (!result.hasEdge(path.second[i],path.second[j])) 
        {
          result.setEdge(path.second[i],path.second[j],graph_.getEdgeWeight(path.second[i],path.second[j]),graph_.getEdgeColor(path.second[i],path.second[j]));
        }
      }
    }
  }
  result_[src] = result;
}

template <class Graph>
gl::Distance<typename Graph::val_t> Dijkstra<Graph>::pathLength (const idx_t src, const idx_t dest) {
  GL_ASSERT(isInitializedWithGraph_,"Dijkstra::pathLength | Dijkstra has not been initialized with a graph.")
  graph_.checkRange(src,dest);
  
  if (!isInitializedWithSource_[src])
    compute(src);

  return final_[src][dest].first;
}

template <class Graph>
std::pair<bool,typename Graph::idx_list_t> Dijkstra<Graph>::getPath (const idx_t src, const idx_t dest) {
  GL_ASSERT(isInitializedWithGraph_,"Dijkstra::getPath | Dijkstra has not been initialized with a graph.")
  graph_.checkRange(src,dest);  

  if (!isInitializedWithSource_[src])
    compute(src);

  typename Graph::idx_list_t out;
  if (pathLength(src,dest).isInfinite())
  {
    return {false,{}};
  }
  idx_t node = dest;
  while (node != src) {
    out.push_back(node);
    node = final_[src][node].second;
  }
  out.push_back(src);
  std::reverse(out.begin(),out.end());
  return {true,out};
}

template <class Graph>
Graph Dijkstra<Graph>::getSPT (const idx_t src) 
{
  GL_ASSERT(isInitializedWithGraph_,"Dijkstra::getSPT | Dijkstra has not been initialized with a graph.")
  graph_.checkRange(src);  
  if (!isInitializedWithSource_[src])
    compute(src);

  return result_[src];
}

template <class Graph>
void Dijkstra<Graph>::initialize (const Graph graph)
{
  std::vector<bool> isInitializedWithSource (graph.numNodes(),false);
  isInitializedWithSource = isInitializedWithSource_;
  graph_ = graph;

  std::vector<Graph> result (graph.numNodes());
  result_ = result;
  std::vector<result_t> final (graph.numNodes());
  final_ = final;
  isInitializedWithGraph_ = true;
}

} // namespace gl::algorithm  

#endif // GL_DIJKSTRA_HPP