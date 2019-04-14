#ifndef GL_PROPERTY_HPP
#define GL_PROPERTY_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Property function implementations
///////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
using idx_t = typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t;
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
using val_t = typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/* \internal getter for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodes() const {
  return _numNodes;
}

/* \internal setter for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodes(const idx_t& numNodes) {
  _numNodes = numNodes;
}

/* \internal increment for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesIncrement (const idx_t& increment) {
  _numNodes += increment;
}
/* \internal decrement for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesDecrement (const idx_t& decrement) {
  _numNodes -= decrement;
}

/* \internal getter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges() const {
  return _numEdges;
}

/* \internal setter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges(const idx_t& numEdges) {
  _numEdges = numEdges;
}

/* \internal increment for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesIncrement (const idx_t& increment) {
  _numEdges += increment;
}
/* \internal decrement for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesDecrement (const idx_t& decrement) {
  _numEdges -= decrement;
}
/* \internal getter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::name() const {
  return _name;
}

/* \internal setter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::name(const std::string& name) {
  _name = name;
}

} // namespace gl

#endif // GL_PROPERTY_HPP