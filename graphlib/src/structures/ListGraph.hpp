#ifndef GL_LIST_GRAPH_HPP
#define GL_LIST_GRAPH_HPP

#define GL_ENABLE_IF_DIRECTED(RETURN_TYPE) template <typename DIR = DIRECTION> typename std::enable_if<std::is_same<DIR, Directed>::value, RETURN_TYPE>::type

#define GL_ENABLE_IF_UNDIRECTED(RETURN_TYPE) template <typename DIR = DIRECTION> typename std::enable_if<std::is_same<DIR, Undirected>::value, RETURN_TYPE>::type

#include "Graph.hpp"

#include <vector>
#include <list>
#include <algorithm>

// necessary forward declaration to prevent linker cycles
namespace gl {
  template <class SCALAR, class DIRECTION>
  class MGraph;
}
#include "MatrixGraph.hpp"
namespace gl {
  
///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Explanations for LGraph
 @brief Derived class, inherits from Graph. It implements an adjacency list data structure.
  */
template <class SCALAR, class DIRECTION>
class LGraph : public Graph<SCALAR, DIRECTION>
{
  public: 
    using idx_t = typename Graph<SCALAR, DIRECTION>::idx_t;
    using val_t = typename Graph<SCALAR, DIRECTION>::val_t;
    using dest_vec_t = typename Graph<SCALAR, DIRECTION>::dest_vec_t;
    using idx_list_t = typename Graph<SCALAR, DIRECTION>::idx_list_t;
    using ordered_list_t = typename Graph<SCALAR, DIRECTION>::ordered_list_t;
    using visit_list_t = typename Graph<SCALAR, DIRECTION>::visit_list_t;
    using BFS_queue_t = typename Graph<SCALAR, DIRECTION>::BFS_queue_t;
    using DFS_queue_t = typename Graph<SCALAR, DIRECTION>::DFS_queue_t;

  struct Node {
    idx_t _end;
    val_t _weight;
    Node (idx_t end = 0, val_t weight = 0) : _end(end),_weight(weight) {}
  };

  protected:
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
    idx_list_t getNeighbours (const idx_t) const;
    idx_list_t getUnvisitedNeighbours (const idx_t, const std::vector<bool>) const;
    dest_vec_t getNeighbourWeights (const idx_t) const;    
    idx_t getDegree (const idx_t) const;    
    MGraph<SCALAR, DIRECTION> toMatrix () const;
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

/**
 * @brief Creates an empty Graph using an adjacency list storage format.
 * @copydoc Graph<SCALAR,DIRECTION>::Graph()
 */
template <class SCALAR, class DIRECTION>
LGraph<SCALAR, DIRECTION>::LGraph(idx_t numNodes) : 
                       Graph<SCALAR, DIRECTION>(numNodes),
                       _edges(numNodes) {}


/**
 * @brief Outputs an MGraph<SCALAR, DIRECTION> with the same edges as *this.
 */
template <class SCALAR, class DIRECTION>
MGraph<SCALAR, DIRECTION> LGraph<SCALAR, DIRECTION>::toMatrix () const {
  gl::MGraph<SCALAR, DIRECTION> out(Graph<SCALAR, DIRECTION>::numNodes());
  for (idx_t start = 0; start < _edges.size(); ++start) {
    for (auto & end: _edges[start]) {
      out.setEdge(start,end._end,end._weight);
    }
  }
  return out;
}

/** @copydoc Graph<SCALAR,DIRECTION>::setEdge() */
template <class SCALAR, class DIRECTION>
void LGraph<SCALAR, DIRECTION>::setEdge(const idx_t start, const idx_t end, const val_t weight) {
  Graph<SCALAR, DIRECTION>::checkRange(start,end);
  if (hasEdge(start,end)) {
    updateEdge(start,end,weight);
  } else {
    _edges[start].push_back(Node(end,weight));
  }
}

/** @copydoc Graph<SCALAR,DIRECTION>::updateEdge() */
template <class SCALAR, class DIRECTION>
void LGraph<SCALAR, DIRECTION>::updateEdge(const idx_t start, const idx_t end, const val_t weight) {
  Graph<SCALAR, DIRECTION>::checkRange(start,end);
  auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
  [&end](const Node& node){ return node._end == end;});
  (*it)._weight = weight;
}

/** @copydoc Graph<SCALAR,DIRECTION>::delEdge() */
template <class SCALAR, class DIRECTION>
void LGraph<SCALAR, DIRECTION>::delEdge(const idx_t start, const idx_t end) {
  Graph<SCALAR, DIRECTION>::checkRange(start,end);
  auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
  [&end](const Node& node){ return node._end == end;});
  _edges[start].erase(it);
}

/** @copydoc Graph<SCALAR,DIRECTION>::hasEdge() */
template <class SCALAR, class DIRECTION>
bool LGraph<SCALAR, DIRECTION>::hasEdge (const idx_t start, const idx_t end) const {
  Graph<SCALAR, DIRECTION>::checkRange(start,end);
  auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
  [&end](const Node& node){ return node._end == end;});
  return it != _edges[start].end();
}

/** @copydoc Graph<SCALAR,DIRECTION>::getWeight() */
template <class SCALAR, class DIRECTION>
typename LGraph<SCALAR, DIRECTION>::val_t LGraph<SCALAR, DIRECTION>::getWeight (const idx_t start, const idx_t end) const {
  Graph<SCALAR, DIRECTION>::checkRange(start,end);
  auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
  [&end](const Node& node){ return node._end == end;});
  return (*it)._weight;
}

/** @copydoc Graph<SCALAR,DIRECTION>::getNeighbours() */
template <class SCALAR, class DIRECTION>
typename LGraph<SCALAR, DIRECTION>::idx_list_t LGraph<SCALAR, DIRECTION>::getNeighbours (const idx_t node) const {
  idx_list_t out;
  for (idx_t end = 0; end < Graph<SCALAR, DIRECTION>::numNodes(); ++end) {
    if(hasEdge(node, end)) 
      out.push_back(end);
  }
  return out; 
}

/** @copydoc Graph<SCALAR,DIRECTION>::getUnvisitedNeighbours() */
template <class SCALAR, class DIRECTION>
typename LGraph<SCALAR, DIRECTION>::idx_list_t LGraph<SCALAR, DIRECTION>::getUnvisitedNeighbours (const idx_t node, const std::vector<bool> visited) const {
  idx_list_t out;
  for (idx_t end = 0; end < Graph<SCALAR, DIRECTION>::numNodes(); ++end) {
    if(hasEdge(node, end) && !visited[end]) 
      out.push_back(end);
  }
  return out; 
}

/** @copydoc Graph<SCALAR,DIRECTION>::getNeighbourWeights() */
template <class SCALAR, class DIRECTION>
typename LGraph<SCALAR, DIRECTION>::dest_vec_t LGraph<SCALAR, DIRECTION>::getNeighbourWeights (const idx_t node) const {
  dest_vec_t out;
  for (const auto& edge : _edges[node]) {
      out.push_back(std::make_pair(edge._end,edge._weight));
  }
  return out;
}

/** @copydoc Graph<SCALAR,DIRECTION>::getDegree() */
template <class SCALAR, class DIRECTION>
typename LGraph<SCALAR, DIRECTION>::idx_t LGraph<SCALAR, DIRECTION>::getDegree (const idx_t node) const {
  return _edges[node].size();
}


#undef GL_ENABLE_IF_DIRECTED
#undef GL_ENABLE_IF_UNDIRECTED

} /* namespace gl */


#endif /* GL_LIST_GRAPH_HPP */