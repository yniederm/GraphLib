#ifndef GL_ADJACENCY_LIST_HPP
#define GL_ADJACENCY_LIST_HPP

#include <vector>
#include <iostream>

namespace gl
{
  template <typename T>
  class LGraph
  {
    using val_t = int;
    using idx_t = int;

    struct Node {
      val_t _weight;
      idx_t _end;
      struct Node* next;
    };
    template <typename S>
    struct List {
      struct S* head;
    };
    
    using node_t = Node;
    using rootList_t = List<List>;
    using nodeList_t = List<Node>;

    private:
      rootList_t _root;
      idx_t _numNodes;
      
    public:
      LGraph(idx_t numNodes);
      LGraph(const LGraph& rhs);
      ~LGraph();
      void setEdge(idx_t start, idx_t end, val_t value);
      void delEdge(idx_t start, idx_t end);
      bool hasEdge (idx_t start, idx_t end) const;
      val_t getWeight (idx_t start, idx_t end) const;
  };
  
  template <typename T>
  LGraph<T>::LGraph(idx_t numNodes) : _numNodes(numNodes) {
    _edges = new rootList_t;
    auto rootPointer = _edges.head;
    for(idx_t i = 0; i < _numNodes-1; i++)
    {
      
    }
    
  }
  template <typename T>
  LGraph<T>::LGraph(const LGraph& rhs) {

  }
  template <typename T>
  LGraph<T>::~LGraph() {}

  template <typename T>
  void LGraph<T>::setEdge(idx_t start, idx_t end, val_t value) {
    
  }

  template <typename T>
  void LGraph<T>::delEdge(idx_t start, idx_t end) {
    _weight[start][end] = 0;
    _adjacency[start][end] = false;
  }

  template <typename T>
  bool LGraph<T>::hasEdge (idx_t start, idx_t end) const {

    return _edges();
  }

  template <typename T>
  typename LGraph<T>::val_t LGraph<T>::getWeight (idx_t start, idx_t end) const {
    return _weight[start][end];
  }

  template <typename T>
  std::ostream operator<< (std::ostream& s, const LGraph<T>& g) {
    // stuff
    return s;
  }

} // Namespace gl

#endif /* GL_ADJACENCY_LIST_HPP */