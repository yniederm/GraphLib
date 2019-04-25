#ifndef GL_KRUSKAL_HPP
#define GL_KRUSKAL_HPP

#include "../structures/DisjointSets.hpp"

namespace gl::algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Kruskal
 @brief Class that computes a Minimum Spanning Tree using Kruskal's algorithm. A Minimum Spanning Tree (MST) is a subgraph of a given graph that covers all nodes, but wiht minimal edge weight cost.
  */

template <class SCALAR, class STORAGE, class DIR>
class Kruskal {
  using Graph = gl::Graph<SCALAR,STORAGE,DIR>;
  using Edge = typename Graph::Edge;
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using visit_list_t = typename Graph::visit_list_t;

public: 
  /**
   * @brief Constructor. This is where the MST is computed based on a * greedy heuristic that only adds the cheapest edges.
   * @param graph Input graph on which the Minimum Spanning Tree will * be computed.
   */
  Kruskal(const Graph&);

  Kruskal() = delete;
  Kruskal(Kruskal &&) = default;
  Kruskal(const Kruskal &) = default;
  Kruskal &operator=(Kruskal &&) = default;
  Kruskal &operator=(const Kruskal &) = default;
  ~Kruskal();

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
  Graph result_;       ///< @brief MST graph
  val_t cost_;         ///< @brief MST cost (sum of all edge weights)
};

///////////////////////////////////////////////////////////
//    DisjointSets function implementations
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class SCALAR, class STORAGE, class DIR>
Kruskal<SCALAR,STORAGE,DIR>::~Kruskal() {}

template <class SCALAR, class STORAGE, class DIR>
Kruskal<SCALAR,STORAGE,DIR>::Kruskal(const Graph& graph) {
  std::vector<Edge> edges;
  Graph result(graph.numNodes(),std::string(std::string("MST of ")+graph.getGraphLabel()));
  val_t cost {0};
  // visit_list_t visited(graph.numNodes(), false);
  DisjointSets disjointSets(graph.numNodes());

  // get vector of all edges in the graph
  for (auto it = graph.edge_cbegin(); it != graph.edge_cend(); ++it) {
    edges.push_back(*it);
  }
  // sort edges by increasing weight
  std::sort(edges.begin(),edges.end(),[](const Edge& lhs, const Edge& rhs){
    return lhs.weight() < rhs.weight();
  });
  
  // construct MST
  for(auto edge : edges) {
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

    // if (visited[edge.source()] + visited[edge.dest()] < 2) {
    //   visited[edge.source()] = true;
    //   visited[edge.dest()] = true;
    //   result.setEdge(edge);
    //   cost += edge.weight();
    // }
  }

  result_ = result;
  cost_ = cost;
}

template <class SCALAR, class STORAGE, class DIR>
typename Kruskal<SCALAR,STORAGE,DIR>::val_t Kruskal<SCALAR,STORAGE,DIR>::getCost () const {
  return cost_;
}

template <class SCALAR, class STORAGE, class DIR>
typename Kruskal<SCALAR,STORAGE,DIR>::Graph Kruskal<SCALAR,STORAGE,DIR>::getMST () const {
  auto result = result_;
  return result;
}

} // namespace gl::algorithm 

#endif // GL_Kruskal_HPP