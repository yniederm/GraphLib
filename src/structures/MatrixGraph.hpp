#ifndef GL_MATRIX_GRAPH_HPP
#define GL_MATRIX_GRAPH_HPP

#include "Graph.hpp"

#include <vector>

namespace gl 
{
  template <class SCALAR>
  class LGraph;
}
#include "ListGraph.hpp"
namespace gl 
{
  /** Explanations for MGraph
   @brief Derived class, inherits from Graph. It implements an adjancency matrix data structure.
   */
  template <class SCALAR>
  class MGraph : public Graph<SCALAR>
  {
    public: 
      using idx_t = typename Graph<SCALAR>::idx_t;
      using val_t = typename Graph<SCALAR>::val_t;
      using dest_vec_t = typename Graph<SCALAR>::dest_vec_t;

    struct Node {
      bool _edge;
      val_t _weight;
      Node (bool edge = false, val_t weight = 0) : _edge(edge),_weight(weight) {}
    };

    protected:
      using matrix_row_t = std::vector<Node>;
      using matrix_t = std::vector<matrix_row_t>;

    protected:
      matrix_t _matrix;
      
    public:
      MGraph(idx_t);
      ~MGraph() {};
      void setEdge (const idx_t, const idx_t, const val_t = 1);
      void updateEdge (const idx_t, const idx_t, const val_t);
      void delEdge (const idx_t,const idx_t);
      bool hasEdge (const idx_t, const idx_t) const;
      val_t getWeight (const idx_t, const idx_t) const;
      dest_vec_t getNeighbours (const idx_t) const;   
      idx_t getDegree (const idx_t) const;    
      LGraph<SCALAR> toList (); 
  };

  template <class SCALAR>
  MGraph<SCALAR>::MGraph(idx_t numNodes) : Graph<SCALAR>(numNodes) {
        matrix_t matrix;

        Node emptyNode;
        matrix_row_t tempRow(numNodes,emptyNode);
        for (idx_t col = 0; col < numNodes; ++col) {
          matrix.emplace_back(tempRow);
        }
        _matrix = matrix;
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
        if (hasEdge(i,j)) out.setEdge(i,j,_matrix[i][j]._weight); 
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
    _matrix[start][end]._weight = weight;
    _matrix[start][end]._edge = true;
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
    _matrix[start][end]._weight = weight;
  }

/**
 * @brief Deletes the edge going from start to end.
 * @param start edge origin point
 * @param end edge end point
 */
  template <class SCALAR>
  void MGraph<SCALAR>::delEdge(const idx_t start, const idx_t end) {
    Graph<SCALAR>::checkRange(start, end);
    _matrix[start][end]._weight = SCALAR(0);
    _matrix[start][end]._edge = false;
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
    return _matrix[start][end]._edge;
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
    return _matrix[start][end]._weight;
  }

  template <class SCALAR>
  typename MGraph<SCALAR>::dest_vec_t MGraph<SCALAR>::getNeighbours (const idx_t start) const {
    dest_vec_t out;
    for (idx_t end = 0; end < Graph<SCALAR>::numNodes(); ++end) {
      if(hasEdge(start, end)) 
        out.push_back(std::make_pair(end,getWeight(start,end)));
    }
    return out; 
  }

  template <class SCALAR>
  typename MGraph<SCALAR>::idx_t MGraph<SCALAR>::getDegree (const idx_t node) const {
    idx_t count = 0;
    for (const auto end : _matrix[node]) {
      if (end._edge) ++count;
    }
    return count;
  }
} /* Namespace gl */

#endif /* GL_MATRIX_GRAPH_HPP */
