#ifndef GL_ADJACENCY_LIST_H
#define GL_ADJACENCY_LIST_H

#include <vector>
#include <iostream>

namespace gl
{
  class LGraph
  {
    using val_t = int;
    using idx_t = int;

    struct Node {
      val_t _weight;
      idx_t _end;
      struct Node* next;
    };
    template <T>
    struct List {
      struct T* head;
    }
    
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
  
  LGraph::LGraph(idx_t numNodes) : _numNodes(numNodes) {
    _edges = new rootList_t;
    auto rootPointer = _edges.head;
    for(idx_t i = 0; i < _numNodes-1; i++)
    {
      
    }
    
  }
  LGraph::LGraph(const LGraph& rhs) {

  }
  LGraph::~LGraph() {}

  void LGraph::setEdge(idx_t start, idx_t end, val_t value) {
    
  }

  void LGraph::delEdge(idx_t start, idx_t end) {
    _weight[start][end] = 0;
    _adjacency[start][end] = false;
  }

  bool LGraph::hasEdge (idx_t start, idx_t end) const {

    return _edges();
  }

  val_t LGraph::getWeight (idx_t start, idx_t end) const {
    return _weight[start][end];
  }

  std::ostream operator<< (std::ostream& s, const LGraph& g) {
    // stuff
    return s;
  }

} // Namespace gl

#endif /* GL_ADJACENCY_LIST_H */