#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <type_traits>
#include <cstdint>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <stack>

namespace gl {

class Matrix;
class List;

class Directed;
class Undirected;

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Explanations for Graph
 @brief Abstract base class that features a few member functions that are the same for both an Adjacency Matrix and List structure.
  */

template <class SCALAR = int, class STORAGE_KIND = gl::List, class DIRECTION = gl::Undirected>
class Graph
{

public:
  using val_t = SCALAR;
  using idx_t = std::size_t;
  using dest_vec_t = std::vector<std::pair<idx_t,val_t>>;
  using idx_list_t = std::vector<idx_t>;
  using ordered_list_t = std::list<idx_t>;
  using visit_list_t = std::vector<bool>;
  using BFS_queue_t = std::deque<idx_t>;
  using DFS_queue_t = std::stack<idx_t>;

  /** 
   @brief Represents an edge in an adjacency matrix.
    */
  struct MatrixNode {
    bool _edge;
    val_t _weight;
    MatrixNode (bool edge = false, val_t weight = 0) : _edge(edge),_weight(weight) {}
  };

  /** 
   @brief Represents an edge in an adjacency list.
    */
  struct ListNode {
    idx_t _end;
    val_t _weight;
    ListNode (idx_t end = 0, val_t weight = 0) : _end(end),_weight(weight) {}
  };

  using matrix_t = std::vector<MatrixNode>;
  using nodeList_t = std::list<ListNode>;
  using rootList_t = std::vector<nodeList_t>;
protected:
  int _numNodes;

  std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,matrix_t,rootList_t> _edges;

public: 
  /**
   * @param numNodes Number of nodes/vertices in the graph.
   */
  Graph(int numNodes) : 
        _numNodes(numNodes) { construct(numNodes); }
  ~Graph() {}

private:

  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency matrix storage format.
   * @copydoc Graph<SCALAR,STORAGE_KIND,DIRECTION>::Graph()
   */
  GL_ENABLE_IF_MATRIX
  void construct (const idx_t& numNodes) {
    matrix_t matrix (numNodes*numNodes, MatrixNode()); 
    _edges = matrix;
  }

  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency list storage format.
   * @copydoc Graph<SCALAR,STORAGE_KIND,DIRECTION>::Graph()
   */
  GL_ENABLE_IF_LIST
  void construct (const idx_t& numNodes) {
    rootList_t list (numNodes);
    _edges = list;
  }

public:

///////////////////////////////////////////////////////////
//    Specialized function implementations
///////////////////////////////////////////////////////////


  /**
   * @brief Outputs a graph in Adjacency Matrix storage format with the same edges as this.
   */
  GL_ENABLE_IF_LIST
  gl::Graph<SCALAR,gl::Matrix,DIRECTION> toMatrix() const {
    gl::Graph<SCALAR,gl::Matrix,DIRECTION> out(numNodes());
    for (idx_t start = 0; start < _edges.size(); ++start) {
      for (auto & end: _edges[start]) {
        out.setEdge(start,end._end,end._weight);
      }
    }
    return out;
  }

  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   */
  GL_ENABLE_IF_MATRIX
  gl::Graph<SCALAR,gl::List,DIRECTION> toList() const {
    gl::Graph<SCALAR,gl::List,DIRECTION> out(numNodes());
    for (idx_t i = 0; i < numNodes(); ++i) {
      for (idx_t j = 0; j < numNodes(); ++j) {
        if (hasEdge(i,j)) out.setEdge(i,j,_edges[i*numNodes()+j]._weight); 
      }
    }
    return out;
  }

  /**
   * @name setEdge
   * @brief Sets an edge including start/end points and weight.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   */
  //@{
  /**
   * @brief Adds edge in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1) {
    checkRange(start,end);
    if (hasEdge(start,end)) {
      updateEdge(start,end,weight);
    }
    checkRange(start,end);
    _edges[start].push_back(ListNode(end, weight));
  }
  
  /**
   * @brief Adds edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1) {
    checkRange(start,end);
    if (hasEdge(start,end)) {
      updateEdge(start,end,weight);
    }
    _edges[start].push_back(ListNode(end, weight));
    _edges[end].push_back(ListNode(start, weight));
  }

  /**
   * @brief Adds edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1) {
    if (hasEdge(start,end)) {
      updateEdge(start,end,weight);
    }
    else {
      _edges[start*numNodes()+end]._weight = weight;
      _edges[start*numNodes()+end]._edge = true;
    }
  }
  
  /**
   * @brief Adds edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  void setEdge(idx_t start, idx_t end, const val_t weight = 1) {
    checkRange(start, end);
    if (start > end) std::swap(end, start);
    if (hasEdge(start,end)) {
      updateEdge(start,end,weight);
    }
    else {
      _edges[start*numNodes()+end]._weight = weight;
      _edges[start*numNodes()+end]._edge = true;
    }
  }
  //@}

  /**
   * @name updateEdge
   * @brief Updates the weight of an edge from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   */
  //@{
  /**
   * @brief Updates edge in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    (*it)._weight = weight;
  }

  /**
   * @brief Updates edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    (*it)._weight = weight;

    it = std::find_if(_edges[end].begin(), _edges[end].end(),
    [&start](const ListNode& node){ return node._end == start;});
    (*it)._weight = weight;
  }

  /**
   * @brief Updates edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    checkRange(start,end);
    _edges[start*numNodes()+end]._weight = weight;
  }

  /**
   * @brief Updates edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const val_t weight) {
    checkRange(start,end);
    if (start > end) std::swap(end, start);
    _edges[start*numNodes()+end]._weight = weight;
  }
  //@}

  /**
   * @name delEdge
   * @brief Deletes the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   */
  //@{
  /**
   * @brief Deletes edge in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void delEdge(const idx_t start, const idx_t end) {
    if (!hasEdge(start,end)) {
      std::string errorMessage (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
      throw std::range_error(errorMessage);
    }
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    _edges[start].erase(it);
  }
  
  /**
   * @brief Deletes edge in an Undrected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void delEdge(const idx_t start, const idx_t end) {
    if (!hasEdge(start,end)) {
      std::string errorMessage (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
      throw std::range_error(errorMessage);
    }
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    _edges[start].erase(it);
    it = std::find_if(_edges[end].begin(), _edges[end].end(),
    [&start](const ListNode& node){ return node._end == start;});
    _edges[end].erase(it);
  }

  /**
   * @brief Deletes edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void delEdge (const idx_t start, const idx_t end) {
    checkRange(start,end);
    _edges[start*numNodes()+end]._weight = SCALAR(0);
    _edges[start*numNodes()+end]._edge = false;
  }

  /**
   * @brief Deletes edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void delEdge (idx_t start, idx_t end) {
    checkRange(start,end);
    if (start > end) std::swap(end, start);
    _edges[start*numNodes()+end]._weight = SCALAR(0);
    _edges[start*numNodes()+end]._edge = false;
  }
  //@}

  /**
   * @name hasEdge
   * @brief Checks whether an edge exists from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return true if there exists an edge, false otherwise
   */
  //@{
  /**
   * @brief Checks whether an edge exists in a List Graph.
   */
  GL_ENABLE_IF_LIST
  bool hasEdge(const idx_t start, const idx_t end) const {
    checkRange(start,end);
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    return it != _edges[start].end();
  }

  /**
   * @brief Checks whether an edge exists in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline bool hasEdge(const idx_t start, const idx_t end) const {
    checkRange(start,end);
    return _edges[start*numNodes()+end]._edge;
  }

  /**
   * @brief Checks whether an edge exists in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline bool hasEdge(idx_t start, idx_t end) const {
    checkRange(start,end);
    if (start > end) std::swap(end, start);
    return _edges[start*numNodes()+end]._edge;
  }
  //@}

  /**
   * @name getWeight
   * @brief Finds the weight of the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return weight of the selected edge
   */
  //@{
  /**
   * @brief Finds the weight of an edge in a List Graph.
   */
  GL_ENABLE_IF_LIST
  val_t getWeight(const idx_t start, const idx_t end) const {
    if (!hasEdge(start,end)) {
      std::string errorMessage (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
      throw std::range_error(errorMessage);
    }    
    auto it = std::find_if(_edges[start].begin(), _edges[start].end(),
    [&end](const ListNode& node){ return node._end == end;});
    return (*it)._weight;
  }

  /**
   * @brief Finds the weight of an edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline val_t getWeight(const idx_t start, const idx_t end) const {
    if (!hasEdge(start, end)) {
      std::cout << "There is no edge between " << start << " and " << end << ", returning 0." << std::endl;
      return SCALAR(0);
    }
    return _edges[start*numNodes()+end]._weight;
  }

  /**
   * @brief Finds the weight of an edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline val_t getWeight(idx_t start, idx_t end) const {
    if (start > end) std::swap(end, start);
    if (!hasEdge(start, end)) {
      std::cout << "There is no edge between " << start << " and " << end << ", returning 0." << std::endl;
      return SCALAR(0);
    }
    return _edges[start*numNodes()+end]._weight;
  }
  //@}

  /**
   * @name getNeighbours
   * @brief Returns a list of all endpoints of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours
   */
  //@{
  /**
   * @brief Gets a list of all node neighbours in a List Graph.
   */
  GL_ENABLE_IF_LIST
  idx_list_t getNeighbours (const idx_t node) const {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end)) 
        out.push_back(end);
    }
    return out; 
  }

  /**
   * @brief Gets a list of all node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getNeighbours (const idx_t node) const {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end)) 
        out.push_back(end);
    }
    return out; 
  }
  //@}

  /**
   * @name getUnvisitedNeighbours
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @param visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
  //@{
  /**
   * @brief Gets a list of unvisited node neighbours in a List Graph.
   */
  GL_ENABLE_IF_LIST
  idx_list_t getUnvisitedNeighbours (const idx_t node, const std::vector<bool> visited) const {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end) && !visited[end]) 
        out.push_back(end);
    }
    return out; 
  }
  /**
   * @brief Gets a list of unvisited node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getUnvisitedNeighbours (const idx_t node, const std::vector<bool> visited) const {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end) && !visited[end]) 
        out.push_back(end);
    }
    return out; 
  }
  //@}

  /**
   * @name getNeighbourWeights
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours + weights
   */
  //@{
  /**
   * @brief Gets list & weights of outgoing edges in a List Graph.
   */
  GL_ENABLE_IF_LIST
  dest_vec_t getNeighbourWeights (const idx_t node) const {
    dest_vec_t out;
    for (const auto& edge : _edges[node]) {
        out.push_back(std::make_pair(edge._end,edge._weight));
    }
    return out;
  }
  /**
   * @brief Gets list & weights of outgoing edges in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getNeighbourWeights (const idx_t node) const {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end)) 
        out.push_back(std::make_pair(end,getWeight(node,end)));
    }
    return out; 
  }
  //@}  
  /**
   * @name getUnvisitedEdges
   * @brief Returns a list of endpoints + edge weights of unvisited outgoing edges from start.
   * @param node edge origin point
   * @param visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
  //@{
  /**
   * @brief Gets a list of unvisited edges (weight + neighbour) in a List Graph.
   */
  GL_ENABLE_IF_LIST
  dest_vec_t getUnvisitedEdges (const idx_t node, const std::vector<bool> visited) const {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end) && !visited[end]) 
        out.push_back(std::make_pair(end,getWeight(node,end)));
    }
    return out; 
  }
  /**
   * @brief Gets a list of unvisited edges (weight + neighbour) in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getUnvisitedEdges (const idx_t node, const std::vector<bool> visited) const {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if(hasEdge(node, end) && !visited[end]) 
        out.push_back(std::make_pair(end,getWeight(node,end)));
    }
    return out; 
  }
  //@}

  /**
   * @name getDegree
   * @brief Finds the degree of the given node (i.e. count of all outgoing edges).
   * @param node node whose degree is to be found
   * @return Degree of node
   */
  //@{
  /**
   * @brief Gets the degree of a node in a List Graph.
   */
  GL_ENABLE_IF_LIST
  inline idx_t getDegree (const idx_t node) const {
    return _edges[node].size();
  }

  /**
   * @brief Gets the degree of a node in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_t getDegree (const idx_t node) const {
    idx_t count = 0;
    for (idx_t end = 0; end < numNodes(); ++end) {
      if (hasEdge(node,end)) ++count;
    }
    return count;
  }
  //@}

///////////////////////////////////////////////////////////
//    Base class function implementations
///////////////////////////////////////////////////////////


  /**
   * @name isDirected
   * @brief Returns true if the graph is undirected, false if not.
   * @return true if the graph is undirected, false if not.
   */
  //@{
  /**
   * @brief Version for undirected graphs.
   */
  GL_ENABLE_IF_UNDIRECTED
  inline bool isDirected () const {
    return false;
  }
  /**
   * @brief Version for directed graphs.
   */
  GL_ENABLE_IF_DIRECTED
  inline bool isDirected () const {
    return true;
  }
  //@}

  /**
   * @brief Returns the number of nodes currently in the graph.
   * @return number of nodes in the graph
   */
  inline idx_t numNodes () const {
    return _numNodes;
  }

  /**
   * A quick algorithm that finds cycles in a graph.
   * A cycle in a graph is defined by a back edge (self-loop or edge connecting to an ancestor of the tree given by DFS).
   * An acyclic graph is also known as a tree.
   * @brief Checks whether the given graph containes cycles.
   * @return true if cyclic, false if acyclic
   */
  bool hasCycle () const {
    visit_list_t visited(_numNodes, false);
    idx_list_t neighbourList;

    for(idx_t i = 0; i < _numNodes; i++) {
      neighbourList = getNeighbours(i);
      for(auto neighbour : neighbourList) {
        if (visited[neighbour]) {
          return true;
        } else {
          visited[neighbour] = true;
        }
      }
    }
    return false;
  }

  /**
   * @brief Adds edges in the format "<start> <end> <weight>" found in inFile to the graph.
   * @param inFile file name of input file
   */
  void readFile(const std::string& inFile)
  {
    std::ifstream is;
    is.open(inFile, std::ios::in);
    if (!is.is_open()) {
      std::cout << "Error: failed to open " << inFile << '\n';
    } else {
      idx_t start;
      idx_t end;
      val_t weight;
      while (is >> start >> end >> weight) {
        setEdge(start,end,weight);
      }
    }
  }

  /**
   * @name checkRange
   * @brief Asserts that the given index is within the graph.
   * @param idx1 index that will be range checked
   */
  //@{
  /**
   * @brief Only one index that gets range checked.
   * @param idx1 Index that will be range checked
   */
  inline void checkRange (const idx_t idx1) const {
    if (!(0 <= idx1)) {
      std::string errorMessage (std::string("Negative index: ") + std::to_string(idx1) + std::string("< 0"));
      throw std::range_error(errorMessage);
    } 
    else if (!(idx1 < _numNodes)) {
      std::string errorMessage (std::string("Index too large: ") + std::to_string(idx1) + std::string("<") + std::to_string(_numNodes));
      throw std::range_error(errorMessage);
    }
  }

  /**
   * @brief Two indices that get range checked.
   * @param idx1 First index that will be range checked
   * @param idx2 Second index that will be range checked.
   */
  inline void checkRange (const idx_t idx1, const idx_t idx2) const {
    checkRange(idx1);
    checkRange(idx2);
  }
};

} /* namespace gl */

#endif /* GL_GRAPH_HPP */