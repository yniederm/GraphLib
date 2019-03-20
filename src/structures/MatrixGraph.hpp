#ifndef GL_MATRIX_GRAPH_HPP
#define GL_MATRIX_GRAPH_HPP

#include "Graph.hpp"
#include "ListGraph.hpp"

#include <vector>

namespace gl 
{
  template <class SCALAR>
  class MGraph : public Graph<SCALAR>
  {
    public: 
      using idx_t = typename Graph<SCALAR>::idx_t;
      using val_t = typename Graph<SCALAR>::val_t;
    protected:
      using adj_row_t = std::vector<bool>;
      using adj_mat_t = std::vector<adj_row_t>;
      using weight_row_t = std::vector<val_t>;
      using weight_mat_t = std::vector<weight_row_t>;

    protected:
      adj_mat_t _adjacency;
      weight_mat_t _weight;
      
    public:
      MGraph(idx_t);
      ~MGraph() {};
      void setEdge (const idx_t, const idx_t, const val_t = 1);
      void updateEdge (const idx_t, const idx_t, const val_t);
      void delEdge (const idx_t,const idx_t);
      bool hasEdge (const idx_t, const idx_t) const;
      val_t getWeight (const idx_t, const idx_t) const;
      LGraph<SCALAR> toList (); 
  };

  template <class SCALAR>
  MGraph<SCALAR>::MGraph(idx_t numNodes) : Graph<SCALAR>(numNodes) {
        adj_mat_t adjacency;
        weight_mat_t weight;

        adj_row_t tempAdj (numNodes,0);
        weight_row_t tempWeight (numNodes,false);

        for (idx_t col = 0; col < numNodes; ++col) {
          adjacency.emplace_back(tempAdj);
          weight.emplace_back(tempWeight);
        }
        _adjacency = adjacency;
        _weight = weight;
  }

  /**
   * @brief Outputs an LGraph<SCALAR> with the same edges as *this.
   */
  template <class SCALAR>
  LGraph<SCALAR> MGraph<SCALAR>::toList () {
    idx_t numNodes = Graph<SCALAR>::numNodes();
    LGraph<SCALAR> out(numNodes);
    for (idx_t i = 0; i < numNodes; ++i) {
      for (idx_t j = 0; j < numNodes; ++j) {
        if (hasEdge(i,j)) out.setEdge(i,j,_weight[i][j]); 
      }
    }
    return out;
  }

/**
 * @brief Sets an edge including start/end points and weight.
 * @param start edge origin point
 * @param end edge end point
 * @param weight new edge weight
 */
  template <class SCALAR>
  void MGraph<SCALAR>::setEdge(const idx_t start, const idx_t end, const val_t weight) {
    Graph<SCALAR>::checkRange(start, end);
    _weight[start][end] = weight;
    _adjacency[start][end] = true;
  }
/**
 * @brief Updates the weight of an edge from start to end.
 * @param start edge origin point
 * @param end edge end point
 * @param weight new edge weight
 */
  template <class SCALAR>
  void MGraph<SCALAR>::updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    Graph<SCALAR>::checkRange(start, end);    
    _weight[start][end] = weight;
  }

/**
 * @brief Deletes the edge going from start to end.
 * @param start edge origin point
 * @param end edge end point
 */
  template <class SCALAR>
  void MGraph<SCALAR>::delEdge(const idx_t start, const idx_t end) {
    Graph<SCALAR>::checkRange(start, end);
    _weight[start][end] = SCALAR(0);
    _adjacency[start][end] = false;
  }

/**
 * @brief Checks whether an edge exists from start to end.
 * @param start edge origin point
 * @param end edge end point
 * @return true if there exists an edge, false otherwise
 */
  template <class SCALAR>
  bool MGraph<SCALAR>::hasEdge (const idx_t start, const idx_t end) const {
    Graph<SCALAR>::checkRange(start, end);
    return _adjacency[start][end];
  }

/**
 * @brief Finds the weight of the edge going from start to end.
 * @param start edge origin point
 * @param end edge end point
 * @return weight of the selected edge
 */
  template <class SCALAR>
  typename MGraph<SCALAR>::val_t MGraph<SCALAR>::getWeight (const idx_t start, const idx_t end) const {
    Graph<SCALAR>::checkRange(start, end);
    if (!hasEdge(start, end)) {
      std::cout << "There is no edge between " << start << " and " << end << ", returning 0." << std::endl;
      return SCALAR(0);
    }
    return _weight[start][end];
  }
} /* Namespace gl */

#endif /* GL_MATRIX_GRAPH_HPP */
