#ifndef GL_ADJACENCY_MATRIX_H
#define GL_ADJACENCY_MATRIX_H

#include <vector>
#include <iostream>
#include <cassert>

namespace gl
{

  /** Explanations for MGraph
  /* @file
  /* @brief Implementation of a graph based on an adjacency matrix data structure
   */
  template <typename T>
  class MGraph
  {
    public:
      using val_t = T;
      using idx_t = unsigned int;

    private:
      using adj_row_t = std::vector<bool>;
      using adj_mat_t = std::vector<adj_row_t>;
      using weight_row_t = std::vector<val_t>;
      using weight_mat_t = std::vector<weight_row_t>;

    private:
      adj_mat_t _adjacency;
      weight_mat_t _weight;
      idx_t _numNodes;
      
    public:
      MGraph(idx_t numNodes);
      // MGraph(const LGraph& rhs);
      ~MGraph();
      void setEdge (idx_t start, idx_t end, val_t value = 1);
      void delEdge (idx_t start, idx_t end);
      bool hasEdge (idx_t start, idx_t end) const;
      val_t getWeight (idx_t start, idx_t end) const;
      idx_t numNodes () const;
      void checkRange (idx_t node) const;
      void checkRange (idx_t start, idx_t end) const;
  };
  template <typename T>
  MGraph<T>::MGraph(idx_t numNodes) : _numNodes(numNodes) {
    adj_mat_t adjacency;
    weight_mat_t weight;

    adj_row_t tempAdj (_numNodes,0);
    weight_row_t tempWeight (_numNodes,false);

    for (idx_t col = 0; col < _numNodes; ++col) {
      adjacency.emplace_back(tempAdj);
      weight.emplace_back(tempWeight);
    }
    _adjacency = adjacency;
    _weight = weight;
  }
  // MGraph::MGraph(const LGraph& rhs) {}

  template <typename T>
  MGraph<T>::~MGraph() {}

/**
 * @brief Sets an edge including start/end points and weight.
 * @param start edge origin point
 * @param end edge end point
 * @param value new edge weight
 */
  template <typename T>
  void MGraph<T>::setEdge(idx_t start, idx_t end, val_t value) {
    checkRange(start, end);
    _weight[start][end] = value;
    _adjacency[start][end] = true;
  }

/**
 * @brief Deletes the edge going from start to end.
 * @param start edge origin point
 * @param end edge end point
 */
  template <typename T>
  void MGraph<T>::delEdge(idx_t start, idx_t end) {
    checkRange(start, end);
    _weight[start][end] = T(0);
    _adjacency[start][end] = false;
  }

/**
 * @brief Checks whether an edge exists from start to end.
 * @param start edge origin point
 * @param end edge end point
 * @return true if there exists an edge, false otherwise
 */
  template <typename T>
  bool MGraph<T>::hasEdge (idx_t start, idx_t end) const {
    checkRange(start, end);
    return _adjacency[start][end];
  }

/**
 * @brief Finds the weight of the edge going from start to end.
 * @param start edge origin point
 * @param end edge end point
 * @return weight of the selected edge
 */
  template <typename T>
  typename MGraph<T>::val_t MGraph<T>::getWeight (idx_t start, idx_t end) const {
    checkRange(start, end);
    if (!hasEdge(start, end)) {
      std::cout << "There is no edge between " << start << " and " << end << ", returning 0." << std::endl;
      return T(0);
    }
    return _weight[start][end];
  }

/**
 * @brief Returns the number of nodes currently in the graph.
 * @return number of nodes in the graph
 */
  template <typename T>
  typename MGraph<T>::idx_t MGraph<T>::numNodes () const {
    return _numNodes;
  }

/**
 * @brief Asserts that the given index is within the graph.
 * @param idx index that will be range checked
 */
  template <typename T>
  void MGraph<T>::checkRange (idx_t idx) const {
    assert(0 <= idx);
    assert(idx < _numNodes);
  }

/**
 * @brief Asserts that the given indices are within the graph.
 * @param start first index that will be range checked
 * @param end second index that will be range checked
 */
  template <typename T>
  void MGraph<T>::checkRange (idx_t start, idx_t end) const {
    checkRange(start);
    checkRange(end);
  }

  template <typename T>
  std::ostream& operator<< (std::ostream& s, const MGraph<T>& rhs) {
    using idx_t = typename MGraph<T>::idx_t;
    s << "Edges:" << std::endl;
    for (idx_t i = 0; i < rhs.numNodes(); ++i){
      for(idx_t j = 0; j < rhs.numNodes(); ++j)
      {
        if (rhs.hasEdge(i,j)) {
          s << i << "--" << rhs.getWeight(i,j) << "->" << j << std::endl;
        }
      }      
    }    
    return s;
  }

} // Namespace gl

#endif /* GL_ADJACENCY_MATRIX_H */