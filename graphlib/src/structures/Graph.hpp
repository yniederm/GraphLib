#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include <cstdint>
#include <string>
#include <queue>

namespace gl
{

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
    using visit_list_t = std::vector<bool>;
    using queue_t = std::priority_queue<idx_t>;
  protected:
    idx_t _numNodes;

  public: 
    explicit Graph(idx_t numNodes) : _numNodes(numNodes) {}
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

    // printEdge (?)


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
    idx_t numNodes () const {
      return _numNodes;
    }
    /**
     * @brief Asserts that the given index is within the graph.
     * @param idx index that will be range checked
     */
    void checkRange (const idx_t idx) const {
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
    void checkRange (const idx_t start, const idx_t end) const {
      checkRange(start);
      checkRange(end);
    }
  };

    /**
     * @brief Prints all edges in the format start--weight->end & total edge number.
     * @param os Stream that will be used for output
     * @param rhs Graph that will be printed
     */
  template <class SCALAR>
  std::ostream& operator<< (std::ostream& os, const Graph<SCALAR>& rhs) {
    using idx_t = typename Graph<SCALAR>::idx_t;
    idx_t counter = 0;
    for(idx_t start = 0; start < rhs.numNodes(); start++)
    {
      auto neighbours = rhs.getNeighbourWeights(start);
      for(const auto& edge : neighbours)
      {
        os << start << "--" << edge.second << "->" << edge.first << std::endl;
        ++counter;
      }
    }
    os << "Total Edges: " << counter << std::endl;
    return os;
  }
} /* Namespace gl */

#endif /* GL_GRAPH_HPP */