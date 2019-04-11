#ifndef GL_MATRIX_GRAPH_HPP
#define GL_MATRIX_GRAPH_HPP

#define GL_ENABLE_IF_DIRECTED(RETURN_TYPE) template <typename DIR = DIRECTION> typename std::enable_if<std::is_same<DIR, Directed>::value, RETURN_TYPE>::type

#define GL_ENABLE_IF_UNDIRECTED(RETURN_TYPE) template <typename DIR = DIRECTION> typename std::enable_if<std::is_same<DIR, Undirected>::value, RETURN_TYPE>::type

#include "Graph.hpp"

#include <vector>

// necessary forward declaration to prevent linker cycles
namespace gl {
  template <class SCALAR, class DIRECTION>
  class LGraph;
}
#include "ListGraph.hpp"
namespace gl {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Explanations for MGraph
 @brief Derived class, inherits from Graph. It implements an adjacency matrix data structure.
  */
template <class SCALAR, class DIRECTION>
class MGraph : public Graph<SCALAR,DIRECTION>
{
  public: 
    using idx_t = typename Graph<SCALAR,DIRECTION>::idx_t;
    using val_t = typename Graph<SCALAR,DIRECTION>::val_t;
    using dest_vec_t = typename Graph<SCALAR,DIRECTION>::dest_vec_t;
    using idx_list_t = typename Graph<SCALAR,DIRECTION>::idx_list_t;
    using ordered_list_t = typename Graph<SCALAR,DIRECTION>::ordered_list_t;
    using visit_list_t = typename Graph<SCALAR,DIRECTION>::visit_list_t;
    using BFS_queue_t = typename Graph<SCALAR,DIRECTION>::BFS_queue_t;
    using DFS_queue_t = typename Graph<SCALAR,DIRECTION>::DFS_queue_t;

  struct Node {
    bool _edge;
    val_t _weight;
    Node (bool edge = false, val_t weight = 0) : _edge(edge),_weight(weight) {}
  };

  protected:
    using matrix_t = std::vector<Node>;

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
    idx_list_t getNeighbours (const idx_t) const;
    idx_list_t getUnvisitedNeighbours (const idx_t, const std::vector<bool>) const;
    dest_vec_t getNeighbourWeights (const idx_t) const;   
    idx_t getDegree (const idx_t) const;    
    void makeUndirected ();
    LGraph<SCALAR, DIRECTION> toList (); 
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

/**
 * @brief Creates an empty Graph using an adjacency matrix storage format.
 * @copydoc Graph<SCALAR,DIRECTION>::Graph()
 */
template <class SCALAR, class DIRECTION>
MGraph<SCALAR, DIRECTION>::MGraph(idx_t numNodes) : 
                       Graph<SCALAR, DIRECTION>(numNodes), 
                       _matrix(numNodes*numNodes, Node()) {}

/**
 * @brief Outputs an LGraph<SCALAR, DIRECTION> with the same edges as *this.
 * @return MGraph with the same edges and nodes as *this.
 */
template <class SCALAR, class DIRECTION>
LGraph<SCALAR, DIRECTION> MGraph<SCALAR, DIRECTION>::toList () {
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  LGraph<SCALAR, DIRECTION> out(numNodes);
  for (idx_t i = 0; i < numNodes; ++i) {
    for (idx_t j = 0; j < numNodes; ++j) {
      if (hasEdge(i,j)) out.setEdge(i,j,_matrix[i*numNodes+j]._weight); 
    }
  }
  return out;
}

/** @copydoc Graph<SCALAR,DIRECTION>::setEdge() */
template <class SCALAR, class DIRECTION>
inline void MGraph<SCALAR, DIRECTION>::setEdge(const idx_t start, const idx_t end, const val_t weight) {
  Graph<SCALAR, DIRECTION>::checkRange(start, end);
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  _matrix[start*numNodes+end]._weight = weight;
  _matrix[start*numNodes+end]._edge = true;
}

/** @copydoc Graph<SCALAR,DIRECTION>::updateEdge() */
template <class SCALAR, class DIRECTION>
inline void MGraph<SCALAR, DIRECTION>::updateEdge(const idx_t start, const idx_t end, const val_t weight) {
  Graph<SCALAR, DIRECTION>::checkRange(start, end); 
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();   
  _matrix[start*numNodes+end]._weight = weight;
}

/** @copydoc Graph<SCALAR,DIRECTION>::delEdge() */
template <class SCALAR, class DIRECTION>
inline void MGraph<SCALAR, DIRECTION>::delEdge(const idx_t start, const idx_t end) {
  Graph<SCALAR, DIRECTION>::checkRange(start, end);
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  _matrix[start*numNodes+end]._weight = SCALAR(0);
  _matrix[start*numNodes+end]._edge = false;
}

/** @copydoc Graph<SCALAR,DIRECTION>::hasEdge() */
template <class SCALAR, class DIRECTION>
inline bool MGraph<SCALAR, DIRECTION>::hasEdge (const idx_t start, const idx_t end) const {
  Graph<SCALAR, DIRECTION>::checkRange(start, end);
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  return _matrix[start*numNodes+end]._edge;
}

/** @copydoc Graph<SCALAR,DIRECTION>::getWeight() */
template <class SCALAR, class DIRECTION>
typename MGraph<SCALAR, DIRECTION>::val_t MGraph<SCALAR, DIRECTION>::getWeight (const idx_t start, const idx_t end) const {
  Graph<SCALAR, DIRECTION>::checkRange(start, end);
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  if (!hasEdge(start, end)) {
    std::cout << "There is no edge between " << start << " and " << end << ", returning 0." << std::endl;
    return SCALAR(0);
  }
  return _matrix[start*numNodes+end]._weight;
}

/** @copydoc Graph<SCALAR,DIRECTION>::getNeighbours() */
template <class SCALAR, class DIRECTION>
typename MGraph<SCALAR, DIRECTION>::idx_list_t MGraph<SCALAR, DIRECTION>::getNeighbours (const idx_t node) const {
  idx_list_t out;
  for (idx_t end = 0; end < Graph<SCALAR, DIRECTION>::numNodes(); ++end) {
    if(hasEdge(node, end)) 
      out.push_back(end);
  }
  return out; 
}

/** @copydoc Graph<SCALAR,DIRECTION>::getUnvisitedNeighbours() */
template <class SCALAR, class DIRECTION>
typename MGraph<SCALAR, DIRECTION>::idx_list_t MGraph<SCALAR, DIRECTION>::getUnvisitedNeighbours (const idx_t node, const std::vector<bool> visited) const {
  idx_list_t out;
  for (idx_t end = 0; end < Graph<SCALAR, DIRECTION>::numNodes(); ++end) {
    if(hasEdge(node, end) && !visited[end]) 
      out.push_back(end);
  }
  return out; 
}

/** @copydoc Graph<SCALAR,DIRECTION>::getNeighbourWeights() */
template <class SCALAR, class DIRECTION>
typename MGraph<SCALAR, DIRECTION>::dest_vec_t MGraph<SCALAR, DIRECTION>::getNeighbourWeights (const idx_t node) const {
  dest_vec_t out;
  for (idx_t end = 0; end < Graph<SCALAR, DIRECTION>::numNodes(); ++end) {
    if(hasEdge(node, end)) 
      out.push_back(std::make_pair(end,getWeight(node,end)));
  }
  return out; 
}

/** @copydoc Graph<SCALAR,DIRECTION>::getDegree() */
template <class SCALAR, class DIRECTION>
typename MGraph<SCALAR, DIRECTION>::idx_t MGraph<SCALAR, DIRECTION>::getDegree (const idx_t node) const {
  const idx_t numNodes = Graph<SCALAR, DIRECTION>::numNodes();
  idx_t count = 0;
  for (idx_t end = 0; end < numNodes; ++end) {
    if (_matrix[node*numNodes+end]._edge) ++count;
  }
  return count;
}


#undef GL_ENABLE_IF_DIRECTED
#undef GL_ENABLE_IF_UNDIRECTED

} /* namespace gl */

#endif /* GL_MATRIX_GRAPH_HPP */
