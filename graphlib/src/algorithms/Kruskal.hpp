#ifndef GL_KRUSKAL_HPP
#define GL_KRUSKAL_HPP

#include "../structures/DisjointSets.hpp"

namespace gl::algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** A Minimum Spanning Tree (MST) is a subgraph of a given graph that covers all nodes, but with minimal edge weight cost.
 * @class Kruskal
 * @brief Class that computes a Minimum Spanning Tree using Kruskal's algorithm. 
 */

template <class Graph>
class Kruskal {
  using Edge = typename Graph::Edge;
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using visit_list_t = typename Graph::visit_list_t;

public: 
  Kruskal();                                         ///< Default constructor
  explicit Kruskal(const Graph&);                    ///< Computation constructor

  Kruskal(const Kruskal &) = default;                ///< Copy constructor
  Kruskal(Kruskal &&) noexcept = default;            ///< Move constructor
  Kruskal &operator=(const Kruskal &) = default;     ///< Copy assignment
  Kruskal &operator=(Kruskal &&) noexcept = default; ///< Move assignment
  ~Kruskal() = default;                              ///< Default destructor

  /**
   * @brief Provides a Selector Object to color the edges in the MST.
   * @param[in] color New color for the MST edges.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t src, const idx_t dest)> EdgeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Provides a Selector Object to color the nodes in the MST.
   * @param[in] color New color for the MST nodes.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t node)> NodeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Computation. This is where the MST is computed based on a * greedy heuristic that only adds the cheapest edges.
   * @param graph Input graph on which the Minimum Spanning Tree will * be computed.
   */
  void compute(const Graph& graph);
  /**
   * @brief Computes the cost of the MST (sum of all edge weights in the MST).
   * @return MST cost.
   */
  val_t getCost() const;
  /**
   * @brief Returns a graph that only contains the edges of the MST
   * @return MST Graph.
   */
  Graph getMST() const;

private:
  bool isInitialized_ = false; ///< @brief Boolean storing initialization status
  Graph result_;       ///< @brief MST graph
  val_t cost_;         ///< @brief MST cost (sum of all edge weights)
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
Kruskal<Graph>::Kruskal() : isInitialized_(false) {}

template <class Graph>
Kruskal<Graph>::Kruskal(const Graph& graph) : isInitialized_(false) {
  compute(graph);
}

template <class Graph>
void Kruskal<Graph>::compute(const Graph& graph)
{
  GL_ASSERT(!graph.isDirected(),(std::string("Kruskal::compute | '")+graph.getGraphLabel()+std::string("' is not undirected.\n")))
  std::vector<Edge> edges;
  Graph result(graph.numNodes(),std::string(std::string("MST of ")+graph.getGraphLabel()));
  val_t cost {0};
  DisjointSets disjointSets(graph.numNodes());

  // get vector of all edges in the graph
  for (auto it = graph.edge_cbegin(); it != graph.edge_cend(); ++it) 
  {
    edges.push_back(*it);
  }
  // sort edges by increasing weight
  std::sort(edges.begin(),edges.end(),[](const Edge& lhs, const Edge& rhs)
  {
    return lhs.weight() < rhs.weight();
  });
  
  // construct MST
  for(auto edge : edges) 
  {
    idx_t one = edge.source();
    idx_t two = edge.dest();
    
    idx_t setOne = disjointSets.find(one);
    idx_t setTwo = disjointSets.find(two);

    if (setOne != setTwo)
    {
      result.setEdge(edge);
      cost += edge.weight();
      disjointSets.merge(one,two);
    }
  }

  result_ = result;
  cost_ = cost;
  isInitialized_ = true;
}

template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Graph::idx_t src, const typename Graph::idx_t dest)> Kruskal<Graph>::EdgeSelector (const gl::Color& color) const 
{
  GL_ASSERT(isInitialized_,"Kruskal::EdgeSelector | Kruskal has not been initialized with a graph.")
  return [&color, this](const idx_t src, const idx_t dest) -> std::pair<bool,gl::Color> {
    if (result_.hasEdge(src,dest)) 
      return {true,color};
    else
      return {false,gl::Color()};
  };
}

template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Graph::idx_t node)> Kruskal<Graph>::NodeSelector (const gl::Color& color) const 
{
  GL_ASSERT(isInitialized_,"Kruskal::NodeSelector | Kruskal has not been initialized with a graph.")
  return [&color, this](const idx_t node) -> std::pair<bool,gl::Color> {
    if (0 <= node && node < result_.numNodes())
      return {true,color};
    else return {false,gl::Color()};
  };
}

template <class Graph>
typename Kruskal<Graph>::val_t Kruskal<Graph>::getCost () const 
{
  GL_ASSERT(isInitialized_,"Kruskal::getCost | Kruskal has not been initialized with a graph.")
  return cost_;
}

template <class Graph>
Graph Kruskal<Graph>::getMST () const 
{
  GL_ASSERT(isInitialized_,"Kruskal::getMST | Kruskal has not been initialized with a graph.")
  auto result = result_;
  return result;
}

} // namespace gl::algorithm 

#endif // GL_Kruskal_HPP