#ifndef GL_LIST_GRAPH_HPP
#define GL_LIST_GRAPH_HPP

#include "Graph.hpp"

#include <vector>
#include <list>
#include <algorithm>

namespace gl 
{
  template <class SCALAR>
  class MGraph;
}
#include "MatrixGraph.hpp"
namespace gl
{
  
  /** Explanations for LGraph
   @brief Derived class, inherits from Graph. It implements an adjancency list data structure.
   */
  template <class SCALAR>
  class LGraph : public Graph<SCALAR>
  {
    public: 
      using idx_t = typename Graph<SCALAR>::idx_t;
      using val_t = typename Graph<SCALAR>::val_t;
      using dest_vec_t = typename Graph<SCALAR>::dest_vec_t;

    struct Node {
      idx_t _end;
      val_t _weight;
      Node (idx_t end = 0, val_t weight = 0) : _end(end),_weight(weight) {}
    };

    protected:
      // using node_t = std::pair<idx_t,val_t>;
      // using nodeList_t = std::list<node_t>;
      using nodeList_t = std::list<Node>;
      using rootList_t = std::vector<nodeList_t>;

    protected:
      rootList_t _edges;
      
    public:
      LGraph(idx_t);
      ~LGraph() {};
      void setEdge(const idx_t, const idx_t, const val_t = 1);
      void updateEdge(const idx_t, const idx_t, const val_t);
      void delEdge(const idx_t, const idx_t);
      bool hasEdge (const idx_t, const idx_t) const;
      val_t getWeight (const idx_t, const idx_t) const;
      dest_vec_t getNeighbours (const idx_t) const;    
      MGraph<SCALAR> toMatrix () const;
  };
  
  template <class SCALAR>
  LGraph<SCALAR>::LGraph(idx_t numNodes) : Graph<SCALAR>(numNodes),
                                           _edges(numNodes) {}
  template <class SCALAR>
  MGraph<SCALAR> LGraph<SCALAR>::toMatrix () const {
    gl::MGraph<SCALAR> out(Graph<SCALAR>::numNodes());
    for (idx_t start = 0; start < _edges.size(); ++start) {
      for (auto & end: _edges[start]) {
        // out.setEdge(start,end.first,end.second);
        out.setEdge(start,end._end,end._weight);
      }
    }
    return out;
  }

  template <class SCALAR>
  void LGraph<SCALAR>::setEdge(const idx_t start, const idx_t end, const val_t weight) {
    Graph<SCALAR>::checkRange(start,end);
    if (hasEdge(start,end)) {
      updateEdge(start,end,weight);
    } else {
      _edges[start].push_back(Node(end,weight));
    }
  }

  template <class SCALAR>
  void LGraph<SCALAR>::updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    Graph<SCALAR>::checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const Node& node){ return node._end == end;});
    (*it)._weight = weight;
  }

  template <class SCALAR>
  void LGraph<SCALAR>::delEdge(const idx_t start, const idx_t end) {
    Graph<SCALAR>::checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const Node& node){ return node._end == end;});
    _edges[start].erase(it);
  }

  template <class SCALAR>
  bool LGraph<SCALAR>::hasEdge (const idx_t start, const idx_t end) const {
    Graph<SCALAR>::checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const Node& node){ return node._end == end;});
    return it != _edges[start].end();
  }

  template <class SCALAR>
  typename LGraph<SCALAR>::val_t LGraph<SCALAR>::getWeight (const idx_t start, const idx_t end) const {
    Graph<SCALAR>::checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const Node& node){ return node._end == end;});
    return (*it)._weight;
  }

  template <class SCALAR>
  typename LGraph<SCALAR>::dest_vec_t LGraph<SCALAR>::getNeighbours (const idx_t start) const {
    dest_vec_t out;
    for (const auto& edge : _edges[start]) {
        out.push_back(std::make_pair(edge._end,edge._weight));
    }
    return out;
    
  }
} /* Namespace gl */

#endif /* GL_LIST_GRAPH_HPP */