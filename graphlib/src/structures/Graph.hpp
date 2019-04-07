#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include <cstdint>
#include <string>
#include <queue>
#include <list>
#include <stack>

namespace gl
{

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** Explanations for Graph
 @brief Abstract base class that features a few member functions that are the same for both an Adjacency Matrix and List structure.
  */

template <class SCALAR>
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
protected:
  idx_t _numNodes;
  bool _undirected;

public: 

  /**
   * @param numNodes Number of nodes/vertices in the graph.
   * @param undirected True if graph is undirected, false if directed.
   */
  explicit Graph(idx_t numNodes, bool undirected = 0) : 
                 _numNodes(numNodes), 
                 _undirected(undirected) {}
  virtual ~Graph() {}

  /**
   * @brief Sets an edge including start/end points and weight.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   */
  virtual void setEdge (const idx_t start, const idx_t end, const val_t weight = 1) = 0;

  /**
   * @brief Updates the weight of an edge from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   */
  virtual void updateEdge (const idx_t start, const idx_t end, val_t weight) = 0;

  /**
   * @brief Deletes the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   */
  virtual void delEdge (const idx_t start, const idx_t end) = 0;

  /**
   * @brief Checks whether an edge exists from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return true if there exists an edge, false otherwise
   */
  virtual bool hasEdge (const idx_t start, const idx_t end) const = 0;

  /**
   * @brief Finds the weight of the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return weight of the selected edge
   */
  virtual val_t getWeight (const idx_t start, const idx_t end) const = 0;

  /**
   * @brief Returns a list of all endpoints of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours
   */
  virtual idx_list_t getNeighbours (const idx_t node) const = 0;

  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @param visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
  virtual idx_list_t getUnvisitedNeighbours (const idx_t node, const visit_list_t visited) const = 0;


  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours + weights
   */
  virtual dest_vec_t getNeighbourWeights (const idx_t node) const = 0; 

  /**
   * @brief Finds the degree of the given node (i.e. count of all outgoing edges).
   * @param node node whose degree is to be found
   * @return Degree of node
   */
  virtual idx_t getDegree (const idx_t node) const = 0;

///////////////////////////////////////////////////////////
//    Base class function implementations
///////////////////////////////////////////////////////////

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
   * @brief Returns true if the graph is undirected, false if not.
   * @return true if the graph is undirected, false if not.
   */
  bool isUndirected () const {
    return _undirected;
  }

  /**
   * @brief Asserts that the given index is within the graph.
   * @param idx index that will be range checked
   */
  inline void checkRange (const idx_t idx) const {
    if (!(0 <= idx)) {
      std::string errorMessage (std::string("Negative index: ") + std::to_string(idx) + std::string("< 0"));
      throw std::range_error(errorMessage);
    } 
    else if (!(idx < _numNodes)) {
      std::string errorMessage (std::string("Index too large: ") + std::to_string(idx) + std::string("<") + std::to_string(_numNodes));
      throw std::range_error(errorMessage);
    }
  }

  /**
   * @brief Asserts that the given indices are within the graph.
   * @param start first index that will be range checked
   * @param end second index that will be range checked
   */
  inline void checkRange (const idx_t start, const idx_t end) const {
    checkRange(start);
    checkRange(end);
  }
};

} /* namespace gl */

#endif /* GL_GRAPH_HPP */