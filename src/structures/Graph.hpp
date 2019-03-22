#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <cstdint>

namespace gl
{

  /** Explanations for Graph
   @brief Abstract base class that features a few member functions that             are the same for both an Adjacency Matrix and List structure.
   */

  template <class SCALAR>
  class Graph
  {
  public:
    using val_t = SCALAR;
    using idx_t = std::size_t;
    using dest_vec_t = std::vector<std::pair<idx_t,val_t>>;
  protected:
    idx_t _numNodes;

  public: 
    explicit Graph(idx_t numNodes) : _numNodes(numNodes) {}
    virtual ~Graph() {}
    virtual void setEdge (const idx_t, const idx_t, const val_t = 1) = 0;
    virtual void updateEdge (const idx_t, const idx_t, val_t) = 0;
    virtual void delEdge (const idx_t, const idx_t) = 0;
    virtual bool hasEdge (const idx_t, const idx_t) const = 0;
    virtual val_t getWeight (const idx_t, const idx_t) const = 0;
    virtual dest_vec_t getNeighbours (const idx_t) const = 0; 
    virtual idx_t getDegree (const idx_t) const = 0;

    // printEdge (?)

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
      assert(0 <= idx);
      assert(idx < _numNodes);
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
     * @param s Stream that will be used for output
     * @param rhs Graph that will be printed
     */
  template <class SCALAR>
  std::ostream& operator<< (std::ostream& s, const Graph<SCALAR>& rhs) {
    using idx_t = typename Graph<SCALAR>::idx_t;
    idx_t counter = 0;
    for(idx_t start = 0; start < rhs.numNodes(); start++)
    {
      auto neighbours = rhs.getNeighbours(start);
      for(const auto& edge : neighbours)
      {
        s << start << "--" << edge.second << "->" << edge.first << std::endl;
        ++counter;
      }
    }
    s << "Total Edges: " << counter << std::endl;
    return s;
  }
} /* Namespace gl */

#endif /* GL_GRAPH_HPP */