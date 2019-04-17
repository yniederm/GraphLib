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
#include <iterator>
#include <memory>

#include "Color.hpp"

namespace gl {

class Matrix;
class List;

class Directed;
class Undirected;

///////////////////////////////////////////////////////////
//    Graph Class declaration
///////////////////////////////////////////////////////////

/** 
 * This class has functions to create and edit the graph, as well as access certain properties of the graph. 
 * @class Graph
 * @brief Stores and implements a Graph.
 * @tparam SCALAR Number type used to store edge weights.
 * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
 * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
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
   * @class Edge
   * @brief Represents an edge in a Graph.
   * @tparam SCALAR Number type used to store edge weights.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Edge {
  public:
    Edge (const idx_t& src = 0, const idx_t& dest = 0, const val_t& weight = 0, const Color& color = {}, const bool& exists = false) :
      src_(src), dest_(dest), weight_(weight), exists_(exists), color_(color) {}

    /**
     * @name exists
     * @brief Access to boolean value exists.
     * This signifies the existance of an edge in the graph.
     */
    //@{
    /**
     * @brief Checks whether an edge exists.
     * @return True if exists, false otherwise.
     */
    inline bool exists() const;
    /**
     * @brief Allows changing of existance status of an edge.
     * @param[in] exists New value of boolean exists.
     */
    inline void exists(bool exists);
    //@}
    /**
     * @name source
     * @brief Access to index of source node.
     */
    //@{
    /**
     * @brief Gets the index of the source of the edge.
     * @return index of edge source node.
     */
    inline idx_t source() const;
    /**
     * @brief Allows changing the source of an edge.
     * @param[in] src New value of source index.
     */
    inline void source(idx_t src);
    //@}
    /**
     * @name dest
     * @brief Access to index of destination node.
     */
    //@{
    /**
     * @brief Gets the index of the destination of the edge.
     * @return index of edge destination node.
     */
    inline idx_t dest() const;
    /**
     * @brief Allows changing the destination of an edge.
     * @param[in] dest New value of destination index.
     */
    inline void dest(idx_t dest);
    //@}
    /**
     * @name weight
     * @brief Access to weight of the edge.
     */
    //@{
    /**
     * @brief Gets the weight of the edge.
     * @return Weight of the edge.
     */
    inline val_t weight() const;
    /**
     * @brief Allows changing the weight of an edge.
     * @param[in] weight New value of edge weight.
     */
    inline void weight(val_t weight);
    /**
     * @name color
     * @brief Access to the edge's RGBA color value.
     */
    //@{
    /**
     * @brief Gets the edge's color.
     * @return Color of the edge.
     */
    inline Color color() const;
    /**
     * @brief Allows changing the edge's RGBA color value.
     * @param[in] color New color object. 
     */
    inline void color (const Color& color);
    //@}
    
  private:
    idx_t src_; /**< @brief Source index */
    idx_t dest_; /**< @brief Destination index */ 
    val_t weight_; /**< @brief Edge weight */
    bool exists_; /**< @brief Edge existance */
    Color color_; /**< @brief Edge color */
  };

  /** 
   * @class Node
   * @brief Represents a node in a Graph.
   * @tparam SCALAR Number type used to store node capacities.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Node {

  public:
    Node (idx_t id = 0, val_t capacity = 1, std::string name = "Node") :
      id_(id), name_(name), capacity_(capacity), 
      inDegree_(0), outDegree_(0) {}

    /**
     * @name id
     * @brief Access to node ID.
     */
    //@{
    /**
     * @brief Checks whether an edge exists.
     * @return True if exists, false otherwise.
     */
    inline idx_t id() const;
    /**
     * @brief Allows changing of node ID.
     * @param id New value of node ID.
     */
    inline void id(idx_t id);
    //@}
    /**
     * @name name
     * @brief Access to the name of a node.
     */
    //@{
    /**
     * @brief Gets the name of a node.
     * @return name of the node.
     */
    inline const char* name() const;
    /**
     * @brief Allows changing the name of a node.
     * @param name New value of node name.
     */
    inline void name(const char* name);
    //@}
    /**
     * @name capacity
     * @brief Access to capacity of the edge.
     */
    //@{
    /**
     * @brief Gets the capacity of the node.
     * @return Capacity of the node.
     */
    inline val_t capacity() const;
    /**
     * @brief Allows changing the capacity of a node.
     * @param capacity New value of node capacity.
     */
    inline void capacity(val_t capacity);
    //@}
    /**
     * @name color
     * @brief Access to the edge's RGBA color value.
     */
    //@{
    /**
     * @brief Gets the edge's color.
     * @return Color of the edge.
     */
    inline Color color() const;
    /**
     * @brief Allows changing the edge's RGBA color value.
     * @param[in] color New color object. 
     */
    inline void color (const Color& color);
    //@}
    /**
     * @name inDegree
     * @brief Access to node in-degree.
     */
    //@{
    /**
     * @brief Gets the in-degree of a node.
     * @return In-degree of a node.
     */
    inline idx_t inDegree() const;
    /**
     * @brief Increments the node in-degree.
     */
    inline void inDegreeIncrement();
    /**
     * @brief Decrements the node in-degree.
     */
    inline void inDegreeDecrement();
    //@}
    /**
     * @name outDegree
     * @brief Access to node out-degree.
     */
    //@{
    /**
     * @brief Gets the out-degree of a node.
     * @return Out-degree of a node.
     */
    inline idx_t outDegree() const;
    /**
     * @brief Increments the node out-degree.
     */
    inline void outDegreeIncrement();
    /**
     * @brief Decrements the node out-degree.
     */
    inline void outDegreeDecrement();
    //@}
    
  private:
    idx_t id_; /**< @brief Node ID */
    std::string name_; /**< @brief Node name */
    val_t capacity_; /**< @brief Node capacity */
    Color color_; /**< @brief Node color */
    idx_t inDegree_; /**< @brief In-degree */
    idx_t outDegree_; /**< @brief Out-degree */
  };

/** 
   * @class Property
   * @brief Stores the properties of a Graph.
   * @tparam SCALAR Number type used to store edge weights.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Property {
  public:
    Property (const idx_t& numNodes, const std::string& name = "Graph", const idx_t& numEdges = 0) :
      _numNodes(numNodes), _name(name), _numEdges(0) {}
    Property (const Property& property) :
      _numNodes(property._numNodes), _name(property._name), _numEdges(property._numEdges) {}

    /**
     * @name numNodes
     * @brief Access to the number of nodes in the graph.
     */
    //@{
    /**
     * @brief Gets the number of nodes in the graph.
     * @return Number of nodes in the graph.
     */
    idx_t numNodes() const;
    /**
     * @brief Allows changing the number of nodes in the graph.
     * @param numNodes New value of node count.
     */
    void numNodes(const idx_t& numNodes);
    /**
     * @brief Increments the number of nodes in the graph.
     * @param increment Number of nodes that will be added to the graph.
     */
    void numNodesIncrement(const idx_t& increment = 1);
    /**
     * @brief Decrements the number of nodes in the graph.
     * @param decrement Number of nodes that will be removed from the graph.
     */
    void numNodesDecrement(const idx_t& decrement = 1);
    //@}
    /**
     * @name numEdges
     * @brief Access to the number of edges in the graph.
     */
    //@{
    /**
     * @brief Gets the number of edges in the graph.
     * @return Number of edges in the graph.
     */
    idx_t numEdges() const;
    /**
     * @brief Allows changing the number of edges in the graph.
     * @param numEdges New value of edge count.
     */
    void numEdges(const idx_t& numEdges);
    /**
     * @brief Increments the number of edges in the graph.
     * @param increment Number of nodes that will be added to the graph.
     */
    void numEdgesIncrement(const idx_t& increment = 1);
    /**
     * @brief Decrements the number of edges in the graph.
     * @param decrement Number of edges that will be removed from the graph.
     */
    void numEdgesDecrement(const idx_t& decrement = 1);
    //@}
    /**
     * @name name
     * @brief Access to name of the graph.
     */
    //@{
    /**
     * @brief Gets the name of the graph.
     * @return Graph name.
     */
    std::string name() const;
    /**
     * @brief Allows changing the name of the graph.
     * @param name New graph name.
     */
    void name(const std::string& name);
    //@}
    
  private:
    idx_t _numNodes; /**< number of nodes in the graph */
    idx_t _numEdges; /**< number of edges in the graph */ 
    std::string _name; /**< name of the graph */
  };

  using matrix_t = std::vector<Edge>;
  using nodeList_t = std::list<Edge>;
  using rootList_t = std::vector<nodeList_t>;
protected:
  Property property_;

  std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,matrix_t,rootList_t> edges_;

public: 
  /**
   * @param numNodes Number of nodes/vertices in the graph.
   * @param name Name of the graph.
   */
  Graph(const int& numNodes, const std::string& name = "Graph") : 
        property_(numNodes,name,0) { construct(); }
  /**
   * @param property Properties for a graph.
   */
  Graph(const Property& property) : 
        property_(property) { construct(); }
  ~Graph() {}

private:

  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency matrix storage format.
   */
  GL_ENABLE_IF_MATRIX
  void construct () {
    matrix_t matrix (numNodes()*numNodes(), Edge()); 
    for (idx_t i = 0; i < numNodes(); ++i) {
      for (idx_t j = 0; j < numNodes(); ++j) {
        matrix[i*numNodes()+j].source(i);
        matrix[i*numNodes()+j].dest(j);
      }
    }
    edges_ = matrix;
  }

  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency list storage format.
   */
  GL_ENABLE_IF_LIST
  void construct () {
    rootList_t list (numNodes());
    edges_ = list;
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
    gl::Graph<SCALAR,gl::Matrix,DIRECTION> out(numNodes(), name());
    for (idx_t start = 0; start < edges_.size(); ++start) {
      for (auto & end: edges_[start]) {
        out.setEdge(start,end.dest(),end.weight(),end.color());
      }
    }
    return out;
  }

  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  gl::Graph<SCALAR,List,Directed> toList() const {
    gl::Graph<SCALAR,List,Directed> out(numNodes(), name());
    for (idx_t i = 0; i < numNodes(); ++i) {
      for (idx_t j = 0; j < numNodes(); ++j) {
        if (hasEdge(i,j)) {
          out.setEdge(i,j,edges_[i*numNodes()+j].weight(),edges_[i*numNodes()+j].color()); 
        }
      }
    }
    return out;
  }
  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  gl::Graph<SCALAR,List,Undirected> toList() const {
    gl::Graph<SCALAR,List,Undirected> out(numNodes(), name());
    for (idx_t i = 0; i < numNodes(); ++i) {
      for (idx_t j = i; j < numNodes(); ++j) {
        if (hasEdge(i,j)) {
          out.setEdge(i,j,edges_[i*numNodes()+j].weight(),edges_[i*numNodes()+j].color()); 
        }
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
   * @param color (Optional) new edge color
   */
  //@{
  /**
   * @brief Adds edge in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1, const Color& color = Color()) {
    GL_ASSERT((!hasEdge(start,end)),std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));

    edges_[start].push_back(Edge(start, end, weight, color, true));
    property_.numEdgesIncrement();
  }
  
  /**
   * @brief Adds edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1, const Color& color = Color()) {
    GL_ASSERT((!hasEdge(start,end)),std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start].push_back(Edge(start, end, weight, color, true));
    edges_[end].push_back(Edge(end, start, weight, color, true));
    property_.numEdgesIncrement();
  }

  /**
   * @brief Adds edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  void setEdge(const idx_t start, const idx_t end, const val_t weight = 1, const Color& color = Color()) {
    GL_ASSERT((!hasEdge(start,end)),std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].weight(weight);
    edges_[start*numNodes()+end].exists(true);
    edges_[start*numNodes()+end].color(color);
    property_.numEdgesIncrement();
  }
  
  /**
   * @brief Adds edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  void setEdge(idx_t start, idx_t end, const val_t weight = 1, const Color& color = {}) {
    GL_ASSERT((!hasEdge(start,end)),std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    if (start > end) std::swap(end, start);
    edges_[start*numNodes()+end].color(color);
    edges_[start*numNodes()+end].weight(weight);
    if (!hasEdge(start,end)) {
      edges_[start*numNodes()+end].exists(true);
      property_.numEdgesIncrement();
    }
  }
  //@}

  /**
   * @name updateEdge
   * @brief Updates the weight & color of an edge from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   * @param color new edge color
   */
  //@{
  /**
   * @brief Updates edge weight in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).weight(weight);
  }
  /**
   * @brief Updates edge color in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t start, const idx_t end, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).color(color);
  }
  /**
   * @brief Updates edge weight & color in a Directed List Graph.
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).color(color);
    (*it).weight(weight);
  }

  /**
   * @brief Updates edge weight in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).weight(weight);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
    [&start](const Edge& node){ return node.dest() == start;});
    (*it).weight(weight);
  }
  /**
   * @brief Updates edge color in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t start, const idx_t end, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).color(color);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
    [&start](const Edge& node){ return node.dest() == start;});
    (*it).color(color);
  }
  /**
   * @brief Updates edge weight & color in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t start, const idx_t end, const val_t weight, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    (*it).weight(weight);
    (*it).color(color);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
    [&start](const Edge& node){ return node.dest() == start;});
    (*it).weight(weight);
    (*it).color(color);
  }

  /**
   * @brief Updates edge weight in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t start, const idx_t end, const val_t weight) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].weight(weight);
  }
  /**
   * @brief Updates edge color in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t start, const idx_t end, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].color(color);
  }
  /**
   * @brief Updates edge weight & color in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t start, const idx_t end, const val_t weight, const Color& color) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].weight(weight);
    edges_[start*numNodes()+end].color(color);
  }

  /**
   * @brief Updates edge weight in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const val_t weight) {
    if (start > end) std::swap(end, start);
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].weight(weight);
  }
  /**
   * @brief Updates edge color in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const Color& color) {
    if (start > end) std::swap(end, start);
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].color(color);
  }
  /**
   * @brief Updates edge weight & color in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const val_t weight, const Color& color) {
    if (start > end) std::swap(end, start);
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start*numNodes()+end].weight(weight);
    edges_[start*numNodes()+end].color(color);
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
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    edges_[start].erase(it);
    property_.numEdgesDecrement();
  }
  
  /**
   * @brief Deletes edge in an Undrected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void delEdge(const idx_t start, const idx_t end) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    edges_[start].erase(it);
    it = std::find_if(edges_[end].begin(), edges_[end].end(),
    [&start](const Edge& node){ return node.dest() == start;});
    edges_[end].erase(it);
    property_.numEdgesDecrement();
  }

  /**
   * @brief Deletes edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void delEdge (const idx_t start, const idx_t end) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    checkRange(start,end);
    edges_[start*numNodes()+end].weight(SCALAR(0));
    edges_[start*numNodes()+end].exists(false);
    property_.numEdgesDecrement();
  }

  /**
   * @brief Deletes edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void delEdge (idx_t start, idx_t end) {
    GL_ASSERT((hasEdge(start,end)),std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    if (start > end) std::swap(end, start);
    edges_[start*numNodes()+end].weight(SCALAR(0));
    edges_[start*numNodes()+end].exists(false);
    property_.numEdgesDecrement();
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
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    return it != edges_[start].end();
  }

  /**
   * @brief Checks whether an edge exists in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline bool hasEdge(const idx_t start, const idx_t end) const {
    checkRange(start,end);
    return edges_[start*numNodes()+end].exists();
  }

  /**
   * @brief Checks whether an edge exists in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline bool hasEdge(idx_t start, idx_t end) const {
    checkRange(start,end);
    if (start > end) std::swap(end, start);
    return edges_[start*numNodes()+end].exists();
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
    GL_ASSERT(hasEdge(start,end),(std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
    [&end](const Edge& node){ return node.dest() == end;});
    return (*it).weight();
  }

  /**
   * @brief Finds the weight of an edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline val_t getWeight(const idx_t start, const idx_t end) const {
    GL_ASSERT(hasEdge(start,end),(std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start*numNodes()+end].weight();
  }

  /**
   * @brief Finds the weight of an edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline val_t getWeight(idx_t start, idx_t end) const {
    if (start > end) std::swap(end, start);
    GL_ASSERT(hasEdge(start,end),(std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start*numNodes()+end].weight();
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
      if(hasEdge(node, end)) {
        out.push_back(end);
      }
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
    for (const auto& edge : edges_[node]) {
        out.push_back(std::make_pair(edge.dest(),edge.weight()));
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
   * @name getEdgeColor
   * @brief Returns the color of the edgee^from src to dest.
   * @param src edge origin point
   * @param dest edge destination point
   * @return Color of edge src->dest
   */
  //@{
  /**
   * @brief Gets the color of a directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  Color getEdgeColor (const idx_t src, const idx_t dest) const {
    return edges_[src*numNodes()+dest].color();
  }
  /**
   * @brief Gets the color of an undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  Color getEdgeColor (idx_t src, idx_t dest) const {
    if (src > dest) std::swap(src,dest);
    return edges_[src*numNodes()+dest].color();
  }
  /**
   * @brief Gets the color of a List Graph.
   */
  GL_ENABLE_IF_LIST
  Color getEdgeColor (const idx_t src, const idx_t dest) const {
    auto it = std::find_if(edges_[src].begin(), edges_[src].end(),
    [&dest](const Edge& node){ return node.dest() == dest;});
    return (*it).color();
  }
  //@}

  /**
   * @name getDegree
   * @brief Finds the degree numNodesof the given node (i.e. count of all outgoing edges).
   * @param node node whose degree is to be found
   * @return Degree of node
   */
  //@{
  /**
   * @brief Gets the degree of a node in a List Graph.
   */
  GL_ENABLE_IF_LIST
  inline idx_t getDegree (const idx_t node) const {
    return edges_[node].size();
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
   * @brief Returns the name of the graph.
   * @return name of the graph
   */
  inline std::string name () const {
    return property_.name();
  }
  /**
   * @brief Changes the name of the graph.
   * @return New name of the graph
   */
  inline void name (const std::string& name) {
    property_.name(name);
  }
  /**
   * @brief Returns the number of nodes currently in the graph.
   * @return number of nodes in the graph
   */
  inline idx_t numNodes () const {
    return property_.numNodes();
  }

  /**
   * @brief Returns the number of edges currently in the graph.
   * @return number of edges in the graph
   */
  inline idx_t numEdges () const {
    return property_.numEdges();
  }

  /**
   * A quick algorithm that finds cycles in a graph.
   * A cycle in a graph is defined by a back edge (self-loop or edge connecting to an ancestor of the tree given by DFS).
   * An acyclic graph is also known as a tree.
   * @brief Checks whether the given graph containes cycles.
   * @return true if cyclic, false if acyclic
   */
  bool hasCycle () const {
    visit_list_t visited(numNodes(), false);
    idx_list_t neighbourList;

    for(idx_t i = 0; i < numNodes(); i++) {
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
    GL_ASSERT((0 <= idx1),(std::string("Negative index: ") + std::to_string(idx1) + std::string(" < 0")))
    GL_ASSERT((idx1 < numNodes()),("Index " + std::to_string(idx1) + " is larger than the max: " + std::to_string(numNodes()-1)))
  }

  /**
   * @brief Two indices ("edge") that get range checked.
   * @param idx1 First index that will be range checked
   * @param idx2 Second index that will be range checked.
   */
  inline void checkRange (const idx_t idx1, const idx_t idx2) const {
    checkRange(idx1);
    checkRange(idx2);
  }

  class EdgeIterator
  {
  public:
    using self_t = EdgeIterator;
    using val_t = Edge;
    using ref_t = Edge&;
    using pointer_t = Edge*;
    using iterator_category = std::forward_iterator_tag;
    using diff_t = std::ptrdiff_t;
    EdgeIterator() {}
    GL_ENABLE_IF_MATRIX
    EdgeIterator(pointer_t ptr, pointer_t data1, idx_t data2) : ptr_(ptr), data1_(data1), data2_(data2) { }
    GL_ENABLE_IF_LIST
    EdgeIterator(typename nodeList_t::iterator ptr, typename rootList_t::iterator data1, Graph<SCALAR,STORAGE_KIND,DIRECTION>* data2) : ptr_(ptr), data1_(data1), data2_(data2) { }
    GL_ENABLE_IF_MATRIX
    self_t operator++() { 
      ++ptr_;
      while (ptr_ - data1_ < data2_ && !ptr_->exists()) { 
        ptr_++; 
      }
      return *this;
    }
    GL_ENABLE_IF_MATRIX
    self_t operator++(int dummy) { 
      self_t i = *this; 
      ptr_++; 
      while (ptr_ - data1_ < data2_ && !ptr_->exists()) { 
        ptr_++; 
      } 
      return i; 
    }
    GL_ENABLE_IF_LIST
    self_t operator++() { 
      ++ptr_;
      if(ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end())){
        ++data1_;
        while(data1_->size() == 0) ++data1_;
        ptr_ = data1_->begin();
      }
      return *this;
    }
    GL_ENABLE_IF_LIST
    self_t operator++(int dummy) { 
      self_t i = *this; 
      ++ptr_;
      if(ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end())){
        ++data1_;
        while(data1_->size() == 0) ++data1_;
        ptr_ = data1_->begin();
      }
      return i; 
    }
    val_t& operator*() { return *ptr_; }
    val_t* operator->() { return &operator*(); }

    self_t operator=(const self_t& rhs) { 
      ptr_ = rhs.ptr_;
      data1_ = rhs.data1_;
      data2_ = rhs.data2_;
    }
    bool operator==(const self_t& rhs) { return ptr_ == rhs.ptr_ && data1_ == rhs.data1_ && data2_ == rhs.data2_; }
    bool operator!=(const self_t& rhs) { return !operator==(rhs); }
  private:
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value, pointer_t, typename nodeList_t::iterator> ptr_;  //< @brief pointer that will be deferenced in Matrix, iterator over the nodeLists for List
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,pointer_t, typename rootList_t::iterator> data1_;  //< @brief pointer to first element for Matrix, iterator over the rootList for List
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,idx_t, Graph<SCALAR,STORAGE_KIND,DIRECTION>*> data2_;  //< @brief size of adjacency matrix for matrix, pointer to this Graph for List
  };

  class ConstEdgeIterator
  {
  public:
    using self_t = ConstEdgeIterator;
    using val_t = Edge;
    using ref_t = Edge&;
    using pointer_t = Edge*;
    using iterator_category = std::forward_iterator_tag;
    using diff_t = std::ptrdiff_t;

    ConstEdgeIterator() {}
    GL_ENABLE_IF_MATRIX
    ConstEdgeIterator(pointer_t ptr, pointer_t data1, idx_t data2) : ptr_(ptr), data1_(data1), data2_(data2) { }
    GL_ENABLE_IF_LIST
    ConstEdgeIterator(typename nodeList_t::const_iterator ptr, typename rootList_t::const_iterator data1, Graph<SCALAR,STORAGE_KIND,DIRECTION>* data2) : ptr_(ptr), data1_(data1), data2_(data2) { }

    GL_ENABLE_IF_MATRIX
    self_t operator++() { 
      ++ptr_;
      while (ptr_ - data1_ < data2_ && !ptr_->exists()) { 
        ptr_++; 
      }
      return *this; 
    }
    GL_ENABLE_IF_MATRIX
    self_t operator++(int dummy) { 
      self_t i = *this; 
      ptr_++; 
      while (ptr_ - data1_ < data2_ && !ptr_->exists()) { 
        ptr_++; 
      }
      return i; 
    }
    GL_ENABLE_IF_LIST
    self_t operator++() { 
      ++ptr_;
      if(ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end())){
        ++data1_;
        while(data1_->size() == 0) ++data1_;
        ptr_ = data1_->begin();
      }
      return *this;
    }
    GL_ENABLE_IF_LIST
    self_t operator++(int dummy) { 
      self_t i = *this; 
      ++ptr_;
      if(ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end())){
        ++data1_;
        while(data1_->size() == 0) ++data1_;
        ptr_ = data1_->begin();
      }
      return i; 
    }

    self_t operator=(const self_t& rhs) { 
      ptr_ = rhs.ptr_;
      data1_ = rhs.data1_;
      data2_ = rhs.data2_;
    }
    const val_t& operator*() { return *ptr_; }
    const val_t* operator->() { return &operator*(); }
    bool operator==(const self_t& rhs) { return ptr_ == rhs.ptr_ && data1_ == rhs.data1_ && data2_ == rhs.data2_; }
    bool operator!=(const self_t& rhs) { return !operator==(rhs); }

  private:
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value, pointer_t, typename nodeList_t::const_iterator> ptr_;  //< @brief pointer that will be deferenced in Matrix, iterator over the nodeLists for List
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,pointer_t, typename rootList_t::const_iterator> data1_;  //< @brief pointer to first element for Matrix, iterator over the rootList for List
    std::conditional_t<std::is_same<STORAGE_KIND, Matrix>::value,idx_t, Graph<SCALAR,STORAGE_KIND,DIRECTION>*> data2_;  //< @brief size of adjacency matrix for matrix, pointer to this Graph for List
  };
  GL_ENABLE_IF_MATRIX
  EdgeIterator edge_begin() {
    Edge* ptr = &edges_.front();
    Edge* start = &edges_.front();
    idx_t end = numNodes()*numNodes();
    while (!ptr->exists()) {
      ptr++;
    }
    return EdgeIterator(ptr,start,end);
  }
  GL_ENABLE_IF_MATRIX
  EdgeIterator edge_end() {
    return EdgeIterator(&edges_.back()+1,&edges_.front(),numNodes()*numNodes());
  }

  GL_ENABLE_IF_MATRIX
  ConstEdgeIterator edge_cbegin() {
    Edge* ptr = &edges_.front();
    Edge* start = &edges_.front();
    idx_t end = numNodes()*numNodes();
    while (!ptr->exists()) {
      ptr++;
    }
    return ConstEdgeIterator(ptr,start,end);
  }
  GL_ENABLE_IF_MATRIX
  ConstEdgeIterator edge_cend() {
    return ConstEdgeIterator(&edges_.back()+1,&edges_.front(),numNodes()*numNodes());
  }

  GL_ENABLE_IF_LIST
  EdgeIterator edge_begin() {
    auto it = edges_.begin();
    while (it->size()==0) ++it;
    return EdgeIterator(edges_[it-edges_.begin()].begin(), it, this);
  }
  GL_ENABLE_IF_LIST
  EdgeIterator edge_end() {
    return EdgeIterator(edges_.back().end(), edges_.end() - 1, this);
  }

  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cbegin() {
    auto it = edges_.cbegin();
    while (it->size()==0) ++it;
    return ConstEdgeIterator(edges_[it-edges_.begin()].cbegin(), it, this);
  }
  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cend() {
    return ConstEdgeIterator(edges_.back().cend(), edges_.cend() - 1, this);
  }
};

} /* namespace gl */

#endif /* GL_GRAPH_HPP */