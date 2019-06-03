#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <type_traits>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <iterator>

#include "../gl_base.hpp"
#include "Color.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "Property.hpp"
#include "../algorithms/HavelHakimi.hpp"

namespace gl {

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
  using val_t = SCALAR;                                    ///< Value type
  using idx_t = gl::index_type;                            ///< Index type
  using Edge = gl::Edge<val_t>;                            ///< Edge type
  using Node = gl::Node<val_t>;                            ///< Node type
  using dest_vec_t = std::vector<std::pair<idx_t, val_t>>; ///< Destination-Vector type
  using idx_list_t = std::vector<idx_t>;                   ///< Index List type
  using ordered_list_t = std::list<idx_t>;                 ///< Ordered List type
  using visit_list_t = std::vector<bool>;                  ///< Visited-List type
  template <class info_t>
  using BFS_queue_t = std::deque<info_t>; ///< BFS type
  using DFS_queue_t = std::stack<idx_t>;  ///< DFS type

  /* Data structure typedefs */
  using matrix_t = std::vector<Edge>;         ///< @brief Matrix Representation type
  using nodeList_t = std::list<Edge>;         ///< @brief ListNode Representation type
  using rootList_t = std::vector<nodeList_t>; ///< @brief ListRoot Representation type

  /**
   * @brief %Edge_Iterator class.
   * Used to iterate over all Edges in the Graph
   */
  template <bool IsConst = true>
  class Edge_Iterator
  {
  public:
    using value_type = Edge;                                             ///< Edge type
    using reference = std::conditional_t<IsConst, const Edge &, Edge &>; ///< Edge reference type
    using pointer = std::conditional_t<IsConst, const Edge *, Edge *>;   ///< Edge pointer type
    using iterator_category = std::forward_iterator_tag;                 ///< Iterator category
    using difference_type = std::ptrdiff_t;                              ///< Pointer Difference type
    using self_t = Edge_Iterator;                                        ///< EdgeIterator type
    /* typedefs for data members */
    using matrix_iterator_t = std::conditional_t<IsConst, typename matrix_t::const_iterator, typename matrix_t::iterator>;
    using rootList_iterator_t = std::conditional_t<IsConst, typename rootList_t::const_iterator, typename rootList_t::iterator>;
    using list_iterator_t = std::conditional_t<IsConst, typename nodeList_t::const_iterator, typename nodeList_t::iterator>;
    using container_pointer_t = std::conditional_t<IsConst, const Graph<SCALAR, STORAGE_KIND, DIRECTION> *, Graph<SCALAR, STORAGE_KIND, DIRECTION> *>;
    /**
     * @brief Default constructor
     */
    Edge_Iterator() {}
    /**
     * @brief Construct EdgeIterator, only used with Matrix Representation
     * @param[in] ptr Pointer to which edge this iterator should point
     * @param[in] data1 pointer to first element in the matrix
     * @param[in] data2 pointer to the owner data structure
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    Edge_Iterator(matrix_iterator_t ptr, matrix_iterator_t data1, container_pointer_t data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }
    /**
     * @brief Construct EdgeIterator, only used with List Representation
     * @param[in] ptr Pointer to which edge this iterator should point
     * @param[in] data1 iterator over the root vector
     * @param[in] data2 pointer to the owner data structure
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
#endif
    Edge_Iterator(list_iterator_t ptr, rootList_iterator_t data1, container_pointer_t data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }

    /**
     * @brief Move Iterator to next edge (pre-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++()
    {
      ++ptr_;
      while (ptr_ - data1_ < data2_->edges_.size() && !ptr_->exists())
      {
        ++ptr_;
      }
      return *this;
    }
    /**
     * @brief Move Iterator to next edge (post-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ++ptr_;
      while (ptr_ - data1_ < data2_->edges_.size() && !ptr_->exists())
      {
        ++ptr_;
      }
      return i;
    }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
    self_t operator++()
    {
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end()))
        {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return *this;
    }
    GL_ENABLE_IF_LIST
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end()))
        {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return i;
    }
#endif
    /**
     * @brief Const dereference iterator
     * @return A Reference to the underlying edge
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <bool _IsConst = IsConst>
    std::enable_if_t<_IsConst, reference>
#endif
    operator*() const
    {
      return *ptr_;
    }
    /**
     * @brief Non-const dereference iterator
     * @return A Reference to the underlying edge
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <bool _IsConst = IsConst>
    std::enable_if_t<!_IsConst, reference>
#endif
    operator*()
    {
      return *ptr_;
    }
    /**
     * @brief Get underlying edge
     * @return Const pointer to underlying edge
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <bool _IsConst = IsConst>
    std::enable_if_t<_IsConst, pointer>
#endif
    operator->() const
    {
      return &operator*();
    }
    /**
     * @brief Get underlying edge
     * @return Non-const pointer to underlying edge
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <bool _IsConst = IsConst>
    std::enable_if_t<!_IsConst, pointer>
#endif
    operator->()
    {
      return &operator*();
    }
    /**
     * @brief Check if equal
     * @return If both iterators are equal
     */
    bool operator==(const self_t &rhs) { return ptr_ == rhs.ptr_ && data1_ == rhs.data1_ && data2_ == rhs.data2_; }
    /**
     * @brief Check if not equal
     * @return If both iterators are not equal
     */
    bool operator!=(const self_t &rhs) { return !operator==(rhs); }

    /**
     * @brief Construct from Assignment
     * @return If both iterators are not equal
     */
    self_t operator=(const self_t &rhs)
    {
      ptr_ = rhs.ptr_;
      data1_ = rhs.data1_;
      data2_ = rhs.data2_;
    }

  private:
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, matrix_iterator_t, list_iterator_t> ptr_;     ///< @brief [Matrix] Iterator to an element, [List] Iterator over the nodeLists
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, matrix_iterator_t, rootList_iterator_t> data1_; ///< @brief [Matrix] Iterator to first element, [List] Iterator over the rootList
    container_pointer_t data2_; ///< @brief Pointer to owner Graph
  };

  /* Iterator typedefs */
  using EdgeIterator = Edge_Iterator<false>;                            ///< Edge iterator type
  using ConstEdgeIterator = Edge_Iterator<true>;                        ///< Edge const_iterator type
  using NodeIterator = typename std::vector<Node>::iterator;            ///< Node iterator type
  using ConstNodeIterator = typename std::vector<Node>::const_iterator; ///< Node const_iterator type

protected:
  Property property_; ///< @brief Stores various properties of the Graph.
  std::vector<Node> nodes_;                                                              ///< @brief Stores information about all nodes in the Graph.
  std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, matrix_t, rootList_t> edges_; ///< @brief Stores information about all edges in the Graph.

public:
  /**
   * @name Construction
   * Various functions to create/destroy a Graph.
   */
  //@{
  /**
   * @brief Construct Graph from node count and label
   * @param[in] numNodes Number of nodes/vertices in the graph.
   * @param[in] label Label of the graph.
   */
  Graph(const idx_t &numNodes = 0, const std::string &label = "Graph") : property_(numNodes, label)
  {
    construct();
  }
  /**
   * @brief Construct Graph from node count and label
   * @param[in] degreeSeq Degree Sequence of an undirected graph (e.g. 5 1 1 1 1 1").
   * @param[in] label Label of the graph.
   */
  Graph(const std::string &degreeSeq, const std::string &label = "Simple Undirected Graph")
  {
    std::stringstream iss(degreeSeq);
    idx_t degree;
    std::deque<idx_t> degrees;
    while (iss >> degree)
      degrees.push_back(degree);

    GL_ASSERT(gl::algorithm::havelHakimi(degrees), "Degree Sequence is not graphic.")

    idx_t numNodes = degrees.size();
    property_ = Property(numNodes, label);
    property_.numNodes(numNodes);
    construct();

    for (idx_t i = 0; i < numNodes; ++i)
    {
      for (idx_t j = i + 1; j < numNodes; ++j)
      {
        if (degrees[i] > 0 && degrees[j] > 0)
        {
          setEdge(i, j);
          --degrees[i];
          --degrees[j];
        }
      }
    }
  }
  /**
   * @brief Construct Graph from property
   * @param[in] property Properties for a graph.
   */
  Graph(const Property &property) : property_(property)
  {
    construct();
  }
  ~Graph()
  {
  }

  ///////////////////////////////////////////////////////////
  //    Specialized function implementations
  ///////////////////////////////////////////////////////////

  /**
   * @brief Outputs a graph in Adjacency Matrix storage format with the same edges as this.
   * This function only exists for ListGraphs.
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  gl::Graph<SCALAR, gl::Matrix, DIRECTION> toMatrix() const
  {
    gl::Graph<SCALAR, gl::Matrix, DIRECTION> out(numNodes(), getGraphLabel());
    for (idx_t start = 0; start < edges_.size(); ++start)
    {
      for (auto &end : edges_[start])
      {
        out.setEdge(start, end.dest(), end.weight(), end.color());
      }
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Converts an undirected ListGraph to an undirected MatrixGraph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  gl::Graph<SCALAR, gl::Matrix, DIRECTION> toMatrix() const
  {
    gl::Graph<SCALAR, gl::Matrix, DIRECTION> out(numNodes(), getGraphLabel());
    for (idx_t start = 0; start < edges_.size(); ++start)
    {
      for (auto &end : edges_[start])
      {
        if (!out.hasEdge(start, end.dest()))
          out.setEdge(start, end.dest(), end.weight(), end.color());
      }
    }
    return out;
  }
#endif

  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   * This function only exists for MatrixGraphs
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  gl::Graph<SCALAR, gl::List, DIRECTION> toList() const
  {
    gl::Graph<SCALAR, gl::List, DIRECTION> out(numNodes(), getGraphLabel());
    for (auto edge = edge_cbegin(); edge != edge_cend(); ++edge)
    {
      std::cerr << "added " << edge->source() << " " << edge->dest() << "\n";
      out.setEdge(edge->source(), edge->dest(), edge->weight(), edge->color());
    }
    return out;
  }
  //@}
  /**
   * @name Property interface
   * Provides access to the properties of the Graph.
   */
  //@{
  /**
   * @brief Returns the label of the graph.
   * @return label of the graph
   */
  inline std::string getGraphLabel() const
  {
    return property_.label();
  }
  /**
   * @brief Changes the label of the graph.
   * @param[in] label New label of the graph
   */
  inline void setGraphLabel(const std::string &label)
  {
    property_.label(label);
  }
  /**
   * @brief Returns the number of nodes currently in the graph.
   * @return number of nodes in the graph
   */
  inline idx_t numNodes() const
  {
    return property_.numNodes();
  }

  /**
   * @brief Returns the number of edges currently in the graph.
   * @return number of edges in the graph
   */
  inline idx_t numEdges() const
  {
    return property_.numEdges();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_UNDIRECTED
#endif
  /**
   * @brief Returns true if the graph is directed, false if not.
   * @return true if the graph is directed, false if not.
   */
  inline bool isDirected() const
  {
    return false;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Version for directed graphs.
   */
  GL_ENABLE_IF_DIRECTED
  inline bool isDirected() const
  {
    return true;
  }
#endif
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_UNDIRECTED
#endif
  /**
   * @brief Returns true if the graph is undirected, false if not.
   * @return true if the graph is undirected, false if not.
   */
  inline bool isUndirected() const
  {
    return true;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Version for directed graphs.
   */
  GL_ENABLE_IF_DIRECTED
  inline bool isUndirected() const
  {
    return false;
  }
#endif
  /**
   * @brief Checks whether the given undirected graph containes cycles using an iterative BFS approach.
   * @return true if cyclic, false if acyclic
   */
  bool hasCycle() const
  {
    idx_t v = 0;
    idx_t parent = 0;
    std::deque<std::pair<idx_t, idx_t>> queue;
    idx_list_t tempList;
    visit_list_t visited(numNodes(), false);
    queue.push_front(std::make_pair(v, parent));
    visited[v] = true;

    while (!queue.empty())
    {
      v = queue.front().first;
      parent = queue.front().second;
      queue.pop_front();

      tempList = getNeighbours(v);
      for (auto elem : tempList)
      {
        if (!visited[elem])
        {
          queue.push_front(std::make_pair(elem, v));
          visited[elem] = true;
        }
        else if (elem != parent)
          return true;
      }
    }
    return false;
  }
  /**
   * @name Edge interface
   * Provides access to the properties of the edges in a Graph.
   */
  //@{
  /**
   * @brief Sets an edge including start/end points and weight.
   * @param[in] start edge origin point
   * @param[in] end edge end point
   * @param[in] weight new edge weight
   * @param[in] color (Optional) new edge color
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  void setEdge(const idx_t &start, const idx_t &end, const val_t &weight = 1, const Color &color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));

    edges_[start].push_back(Edge(start, end, weight, color, true));
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
  }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Adds edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void setEdge(const idx_t &start, const idx_t &end, const val_t &weight = 1, const Color &color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start].push_back(Edge(start, end, weight, color, true));
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
    if (start != end)
    { // for avoiding double-adding self loops
      edges_[end].push_back(Edge(end, start, weight, color, true));
      nodes_[start].inDegreeIncrement();
      nodes_[end].outDegreeIncrement();
    }
  }

  /**
   * @brief Adds edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  void setEdge(const idx_t &start, const idx_t &end, const val_t &weight = 1, const Color &color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
    edges_[start * numNodes() + end].exists(true);
    edges_[start * numNodes() + end].color(color);
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
  }

  /**
   * @brief Adds edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  void setEdge(idx_t start, idx_t end, const val_t &weight = 1, const Color &color = {})
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].color(color);
    edges_[start * numNodes() + end].weight(weight);
    if (!hasEdge(start, end))
    {
      edges_[start * numNodes() + end].exists(true);
      property_.numEdgesIncrement();
      nodes_[start].inDegreeIncrement();
      nodes_[start].outDegreeIncrement();
      nodes_[end].inDegreeIncrement();
      nodes_[end].outDegreeIncrement();
    }
  }
#endif
  /**
   * @brief Adds an edge directly from an Edge object.
   * @param[in] edge Edge that will be copied
   */
  void setEdge(const Edge& edge)
  {
    setEdge(edge.source(), edge.dest(), edge.weight(), edge.color());
  }
  /**
   * @brief Adds edges in the format "<start> <end> <weight>" found in inFile to the graph.
   * @param[in] inFile file name of input file
   */
  void addEdgesFromFile(const std::string &inFile)
  {
    std::ifstream is;
    is.open(inFile, std::ios::in);
    GL_ASSERT(is.is_open(),std::string(std::string("Error: failed to open ")+inFile))

    idx_t start, end;
    val_t weight;
    while (is >> start >> end >> weight)
    {
      setEdge(start, end, weight);
    }
  }

  /**
   * @brief Updates edge properties. Parameters "start" & "end" mandatory, the rest optional.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight (Optional) New edge weight
   * @param[in] color (Optional) New edge color
   */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
  inline void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight, const gl::Color& color) {}
#endif
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  template <typename ... Args, typename STORAGE = STORAGE_KIND, typename DIR = DIRECTION, GL_ENABLE_IF_LIST_DIRECTED_T>
  inline void updateEdge(const idx_t& start, const idx_t& end, const Args&... args)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    updateEdgeInternal(it, args...);
  }
  template <typename ... Args, typename STORAGE = STORAGE_KIND, typename DIR = DIRECTION, GL_ENABLE_IF_LIST_UNDIRECTED_T>
  inline void updateEdge(const idx_t& start, const idx_t& end, const Args&... args)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    updateEdgeInternal(it, args...);
    it = std::find_if(edges_[end].begin(), edges_[end].end(),
                      [&start](const Edge &node) { return node.dest() == start; });
    updateEdgeInternal(it, args...);
  }
  template <typename ... Args, typename STORAGE = STORAGE_KIND, typename DIR = DIRECTION, GL_ENABLE_IF_MATRIX_DIRECTED_T>
  inline void updateEdge(const idx_t& start, const idx_t& end, const Args&... args)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    updateEdgeInternal(edges_.data()+start * numNodes() + end, args...);
  }
  template <typename ... Args, typename STORAGE = STORAGE_KIND, typename DIR = DIRECTION, GL_ENABLE_IF_MATRIX_UNDIRECTED_T>
  inline void updateEdge(const idx_t& start, const idx_t& end, const Args&... args)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    updateEdgeInternal(edges_.data()+start * numNodes() + end, args...);
    updateEdgeInternal(edges_.data()+end * numNodes() + start, args...);
  }

  template <typename Target, typename First, typename ... OtherArgs>
  inline void updateEdgeInternal (const Target& it, First arg, const OtherArgs&... rest)
  {
    throw std::runtime_error(  std::string(__FILE__)
                             + std::string(":")
                             + std::to_string(__LINE__)
                             + std::string(" in ")
                             + std::string(__PRETTY_FUNCTION__)
                             + std::string(": Unknown argument type."));
  }
  template <typename Target, typename ... OtherArgs>
  inline void updateEdgeInternal (const Target& it, const val_t& arg, const OtherArgs&... rest)
  {
    (*it).weight(arg);
    updateEdgeInternal(it,rest...);
  }
  template <typename Target, typename ... OtherArgs>
  inline void updateEdgeInternal (const Target& it, const gl::Color& arg, const OtherArgs&... rest)
  {
    (*it).color(arg);
    updateEdgeInternal(it,rest...);
  }
  template <typename Target>
  inline void updateEdgeInternal (const Target& it)
  {
  }
#endif
  /**
   * @brief Deletes the edge going from start to end.
   * @param[in] start edge origin point
   * @param[in] end edge end point
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  void delEdge(const idx_t &start, const idx_t &end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    edges_[start].erase(it);
    property_.numEdgesDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Deletes edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void delEdge(const idx_t &start, const idx_t &end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                          [&end](const Edge &node) { return node.dest() == end; });
    edges_[start].erase(it);
    property_.numEdgesDecrement();
    nodes_[start].inDegreeDecrement();
    nodes_[start].outDegreeDecrement();
    // only do the following if the edge is not a self-loop
    if (start != end) {
      it = std::find_if(edges_[end].begin(), edges_[end].end(),
                        [&start](const Edge &node) { return node.dest() == start; });
      edges_[end].erase(it);
      nodes_[end].inDegreeDecrement();
      nodes_[end].outDegreeDecrement();
    }
  }

  /**
   * @brief Deletes edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void delEdge(const idx_t &start, const idx_t &end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    checkRange(start, end);
    edges_[start * numNodes() + end].weight(SCALAR(0));
    edges_[start * numNodes() + end].exists(false);
    property_.numEdgesDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
  }

  /**
   * @brief Deletes edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void delEdge(idx_t start, idx_t end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    if (start > end)
      std::swap(end, start);
    edges_[start * numNodes() + end].weight(SCALAR(0));
    edges_[start * numNodes() + end].exists(false);
    property_.numEdgesDecrement();
    nodes_[start].inDegreeDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
    nodes_[end].outDegreeDecrement();
  }
#endif

  /**
   * @brief Checks whether an edge exists from start to end.
   * @param[in] start edge origin point
   * @param[in] end edge end point
   * @return true if there exists an edge, false otherwise
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  bool hasEdge(const idx_t &start, const idx_t &end) const
  {
    checkRange(start, end);
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    return it != edges_[start].end();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Checks whether an edge exists in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline bool hasEdge(const idx_t &start, const idx_t &end) const
  {
    checkRange(start, end);
    return edges_[start * numNodes() + end].exists();
  }

  /**
   * @brief Checks whether an edge exists in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline bool hasEdge(idx_t start, idx_t end) const
  {
    checkRange(start, end);
    if (start > end)
      std::swap(end, start);
    return edges_[start * numNodes() + end].exists();
  }
#endif

  /**
   * @brief Finds the weight of the edge going from start to end.
   * @param[in] start edge origin point
   * @param[in] end edge end point
   * @return weight of the selected edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  val_t getEdgeWeight(const idx_t &start, const idx_t &end) const
  {
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    return (*it).weight();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Finds the weight of an edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline val_t getEdgeWeight(const idx_t &start, const idx_t &end) const
  {
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start * numNodes() + end].weight();
  }

  /**
   * @brief Finds the weight of an edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline val_t getEdgeWeight(idx_t start, idx_t end) const
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start * numNodes() + end].weight();
  }
#endif
  /**
   * @brief Returns the color of the edge from src to dest.
   * @param[in] src edge origin point
   * @param[in] dest edge destination point
   * @return Color of edge src->dest
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the color of an edge in a directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
#endif
  Color getEdgeColor(const idx_t &src, const idx_t &dest) const
  {
    return edges_[src * numNodes() + dest].color();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the color of an edge in an undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  Color getEdgeColor(idx_t src, idx_t dest) const
  {
    if (src > dest)
      std::swap(src, dest);
    return edges_[src * numNodes() + dest].color();
  }
  /**
   * @brief Gets the color of an edge in a List Graph.
   */
  GL_ENABLE_IF_LIST
  Color getEdgeColor(const idx_t &src, const idx_t &dest) const
  {
    auto it = std::find_if(edges_[src].begin(), edges_[src].end(),
                           [&dest](const Edge &node) { return node.dest() == dest; });
    return (*it).color();
  }
#endif

  /**
   * @brief EdgeIterator to the first edge
   * @return Iterator to the first edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  EdgeIterator edge_begin()
  {
    auto ptr = edges_.begin();
    if (numEdges() > 0) {
      while (!ptr->exists())
      {
        ++ptr;
      }
    }
    else
    {
      ptr = edges_.end();
    }
    return Edge_Iterator<false>(ptr, edges_.begin(), this);
  }
  /**
   * @brief EdgeIterator to behind the last edge
   * @return Iterator to behind the last edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  EdgeIterator edge_end()
  {
    return Edge_Iterator<false>(edges_.end(), edges_.begin(), this);
  }
  /**
   * @brief ConstEdgeIterator to the first edge
   * @return Iterator to the first edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  ConstEdgeIterator edge_cbegin() const
  {
    auto ptr = edges_.cbegin();
    if (numEdges() > 0) {
      while (!ptr->exists())
      {
        ++ptr;
      }
    }
    else
    {
      ptr = edges_.cend();
    }
    return Edge_Iterator<true>(ptr, edges_.cbegin(), this);
  }
  /**
   * @brief ConstEdgeIterator to the last edge
   * @return Iterator to last edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  ConstEdgeIterator edge_cend() const
  {
    return Edge_Iterator<true>(edges_.cend(), edges_.cbegin(), this);
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
  EdgeIterator edge_begin()
  {
    auto ptr = edges_[0].begin(); 
    auto data1 = edges_.begin();
    if (numEdges() > 0) {
      while (data1->size() == 0)
      {
        ++data1;
      }
      ptr = edges_[data1 - edges_.begin()].begin();
    }
    else
    {
      ptr = edges_.back().end();
      data1 = edges_.end()-1;
    }
    return Edge_Iterator<false>(ptr, data1, this);
  }
  GL_ENABLE_IF_LIST
  EdgeIterator edge_end()
  {
    return Edge_Iterator<false>(edges_.back().end(), edges_.end()-1, this);
  }

  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cbegin() const
  {
    auto ptr = edges_[0].cbegin(); 
    auto data1 = edges_.cbegin();
    if (numEdges() > 0) {
      while (data1->size() == 0)
      {
        ++data1;
      }
      ptr = edges_[data1 - edges_.cbegin()].cbegin();
    }
    else
    {
      ptr = edges_.back().cend();
      data1 = edges_.cend()-1;
    }
    return Edge_Iterator<true>(ptr, data1, this);
  }
  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cend() const
  {
    return Edge_Iterator<true>(edges_.back().cend(), edges_.cend()-1, this);
  }
#endif
  //@}
  /**
   * @name Node interface
   * Provides access to the properties of the nodes in the Graph.
   */
  //@{
  /**
   * @brief Returns a list of all endpoints of outgoing edges from start.
   * @param[in] node edge origin point
   * @return List of all direct neighbours
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  idx_list_t getNeighbours(const idx_t &node) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
      {
        out.push_back(end);
      }
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of all node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getNeighbours(const idx_t &node) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
        out.push_back(end);
    }
    return out;
  }
#endif

  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param[in] node edge origin point
   * @param[in] visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  idx_list_t getUnvisitedNeighbours(const idx_t &node, const std::vector<bool> &visited) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(end);
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of unvisited node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getUnvisitedNeighbours(const idx_t &node, const std::vector<bool> &visited) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(end);
    }
    return out;
  }
#endif

  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param[in] node edge origin point
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  dest_vec_t getNeighbourWeights(const idx_t &node) const
  {
    dest_vec_t out;
    for (const auto &edge : edges_[node])
    {
      out.push_back(std::make_pair(edge.dest(), edge.weight()));
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets list & weights of outgoing edges in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getNeighbourWeights(const idx_t &node) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#endif
  /**
   * @brief Returns a list of endpoints + edge weights of unvisited outgoing edges from start.
   * @param[in] node edge origin point
   * @param[in] visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  dest_vec_t getUnvisitedNeighbourWeights(const idx_t &node, const visit_list_t &visited) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of unvisited edges (weight + neighbour) in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getUnvisitedNeighbourWeights(const idx_t &node, const visit_list_t &visited) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#endif
  /**
   * @brief Updates node properties. Parameter "id" mandatory, the rest optional.
   * @param[in] id ID of the node that should be updated.
   * @param[in] label (Optional) New label for the node.
   * @param[in] capacity (Optional) New flow capacity for the node.
   * @param[in] color (Optional) New color for the node.
   * @param[in] position (Optional) New x/y position for the node.
   */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
  inline void updateNode(const idx_t& id, const std::string& label, const val_t& capacity, const gl::Color& color, const std::pair<float,float>& position)
#endif
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /* Unspecialized template for error throwing */
  template <typename First, typename ... OtherArgs>
  inline void updateNode (const idx_t& id, First arg, const OtherArgs&... rest)
#endif 
  {
    throw std::runtime_error(  std::string(__FILE__)
                             + std::string(":")
                             + std::to_string(__LINE__)
                             + std::string(" in ")
                             + std::string(__PRETTY_FUNCTION__)
                             + std::string(": Unknown argument type."));
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  template <typename ... OtherArgs>
  inline void updateNode (const idx_t& id, const std::string& arg, const OtherArgs&... rest) 
  {
    nodes_[id].label(arg);
    updateNode(id, rest...);
  }template <typename ... OtherArgs>
  inline void updateNode (const idx_t& id, const char* arg, const OtherArgs&... rest) 
  {
    nodes_[id].label(arg);
    updateNode(id, rest...);
  }
  template <typename ... OtherArgs>
  inline void updateNode (const idx_t& id, const val_t& arg, const OtherArgs&... rest) 
  {
    nodes_[id].capacity(arg);
    updateNode(id, rest...);
  }
  template <typename ... OtherArgs>
  inline void updateNode (const idx_t& id, const gl::Color& arg, const OtherArgs&... rest) 
  {
    nodes_[id].color(arg);
    updateNode(id, rest...);
  }
  template <typename ... OtherArgs>
  inline void updateNode (const idx_t& id, const std::pair<float,float>& arg, const OtherArgs&... rest) 
  {
    nodes_[id].position(arg);
    updateNode(id, rest...);
  }
  inline void updateNode (const idx_t& id) 
  {
  }
#endif

  /**
   * @brief Finds the label of the given node.
   * @param[in] id ID of the node whose label is to be found.
   * @return Label of node
   */
  inline std::string getNodeLabel(const idx_t &id) const
  {
    return nodes_[id].label();
  }
  /**
   * @brief Finds the flow capacity of the given node.
   * @param[in] id node whose flow capacity is to be found
   * @return Capacity of node
   */
  inline val_t getNodeCapacity(const idx_t &id) const
  {
    return nodes_[id].capacity();
  }
  /**
   * @brief Finds the position of the given node.
   * @param[in] id node whose position is to be found
   * @return pair of floats containing position
   */
  inline std::pair<float, float> getNodePosition(const idx_t &id) const
  {
    return nodes_[id].position();
  }
  /**
   * @brief Finds the degree of the given node (i.e. count of all in- & outgoing edges).
   * @param[in] id node whose degree is to be found
   * @return Degree of node
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_UNDIRECTED
#endif
  inline idx_t getNodeDegree(const idx_t &id) const
  {
    return edges_[id].size();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the degree of a node in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  idx_t getNodeDegree(const idx_t &id) const
  {
    idx_t count = 0;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(id, end))
        ++count;
    }
    return count;
  }
#endif

  /**
   * @brief Gets the in-degree of a node (i.e. count of all incoming edges).
   */
  idx_t getNodeInDegree(const idx_t &id) const
  {
    return nodes_[id].inDegree();
  }
  /**
   * @brief Gets the in-degree of a node (i.e. count of all outgoing edges).
   */
  idx_t getNodeOutDegree(const idx_t &id) const
  {
    return nodes_[id].outDegree();
  }
  /**
   * @brief Returns the color of a node.
   * @param[in] id Node ID
   * @return Color of node with ID "id".
   */
  Color getNodeColor(const idx_t &id) const
  {
    return nodes_[id].color();
  }
  /**
   * @brief Updates node positions in the format "<id> <x-coord> <y-coord>" found in inFile.
   * @param[in] inFile file name of input file
   */
  void readPositionsFromFile (const std::string& inFile)
  {
    std::ifstream is;
    is.open(inFile, std::ios::in);
    GL_ASSERT(is.is_open(),std::string(std::string("Error: failed to open ")+inFile))

    idx_t node;
    float x, y;
    while (is >> node >> x >> y)
    {
      updateNode(node,std::make_pair(x,y));
    }
  }

  /**
   * @brief NodeIterator to the first node
   * @return Iterator to first node
   */
  NodeIterator node_begin()
  {
    return NodeIterator(nodes_.begin());
  }
  /**
   * @brief NodeIterator to behind the last node
   * @return Iterator to behind the last node
   */
  NodeIterator node_end()
  {
    return NodeIterator(nodes_.end());
  }
  /**
   * @brief ConstNodeIterator to the first node
   * @return Iterator to the first node
   */
  ConstNodeIterator node_cbegin() const
  {
    return ConstNodeIterator(nodes_.cbegin());
  }
  /**
   * @brief ConstNodeIterator to behind the last node
   * @return Iterator to behind the last node
   */
  ConstNodeIterator node_cend() const
  {
    return ConstNodeIterator(nodes_.cend());
  }
  //@}
  /**
   * @name checkRange
   * @brief Asserts that the given index/indecies is within the graph.
   */
  //@{
  /**
   * @brief Only one index that gets range checked.
   * @param[in] idx1 Index that will be range checked
   */
  inline void checkRange(const idx_t &idx1) const
  {
    GL_ASSERT((0 <= idx1), (std::string("Negative index: ") + std::to_string(idx1) + std::string(" < 0")))
    GL_ASSERT((idx1 < numNodes()), ("Index " + std::to_string(idx1) + " is larger than the max: " + std::to_string(numNodes() - 1)))
  }

  /**
   * @brief Two indices ("edge") that get range checked.
   * @param[in] idx1 First index that will be range checked
   * @param[in] idx2 Second index that will be range checked.
   */
  inline void checkRange(const idx_t &idx1, const idx_t &idx2) const
  {
    checkRange(idx1);
    checkRange(idx2);
  }
  //@}
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  bool operator== (const Graph<SCALAR,gl::Matrix,DIRECTION>& rhs)
  {
    return property_ == rhs.property_ 
        && edges_ == rhs.edges_
        && nodes_ == rhs.nodes_;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
  bool operator== (const Graph<SCALAR,gl::List,DIRECTION>& rhs)
  {
    return property_ == rhs.property_ 
        && nodes_ == rhs.nodes_;
    // lists are checked more thoroughly, due to potential reordering of elements.
    if (edges_.size() != rhs.edges_.size()) return false;
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      if (edges_[i].size() != rhs.edges_[i].size()) return false;
    }
    for (auto lhs_it = edge_cbegin(); lhs_it != edge_cend(); ++lhs_it)
    {
      auto rhs_it = std::find_if(rhs.edges_[lhs_it->source()].begin(), rhs.edges_[lhs_it->source()].end(),
                           [&lhs_it](const Edge &node) { 
                             return node.dest() == lhs_it->dest()
                                 && node.weight() == lhs_it->weight()
                                 && node.color() == lhs_it->color(); 
                           });
      if (rhs_it == rhs.edges_[lhs_it->source()].end())
        return false;
    }
  }
#endif
  bool operator!= (const Graph<SCALAR,STORAGE_KIND,DIRECTION>& rhs)
  {
    return !operator==(rhs);
  }


  ///////////////////////////////////////////////////////////
  //    Private member declarations
  ///////////////////////////////////////////////////////////

private:
  /**
   * @brief Auxiliary function. Creates an empty Graph using the deduced storage format.
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  // here using matrix
  GL_ENABLE_IF_MATRIX
#endif
  void construct()
  {
    matrix_t matrix(numNodes() * numNodes(), Edge());
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      for (idx_t j = 0; j < numNodes(); ++j)
      {
        matrix[i * numNodes() + j].source(i);
        matrix[i * numNodes() + j].dest(j);
      }
    }
    edges_ = matrix;
    std::vector<Node> nodes();
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      nodes_.push_back(Node(i));
    }
  }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency list storage format.
   */
  GL_ENABLE_IF_LIST
  void construct()
  {
    rootList_t list(numNodes());
    edges_ = list;
    std::vector<Node> nodes();
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      nodes_.push_back(Node(i));
    }
  }
#endif

};

} /* namespace gl */

#endif /* GL_GRAPH_HPP */