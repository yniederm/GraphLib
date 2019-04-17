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
  return numNodes_;
}

/* \internal setter for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodes(const idx_t& numNodes) {
  numNodes_ = numNodes;
}

/* \internal increment for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesIncrement (const idx_t& increment) {
  numNodes_ += increment;
}
/* \internal decrement for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesDecrement (const idx_t& decrement) {
  numNodes_ -= decrement;
}

/* \internal getter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges() const {
  return numEdges_;
}

/* \internal setter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges(const idx_t& numEdges) {
  numEdges_ = numEdges;
}

/* \internal increment for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesIncrement (const idx_t& increment) {
  numEdges_ += increment;
}
/* \internal decrement for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesDecrement (const idx_t& decrement) {
  numEdges_ -= decrement;
}
/* \internal getter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::name() const {
  return name_;
}

/* \internal setter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::name(const std::string& name) {
  name_ = name;
}

} // namespace gl

#endif // GL_PROPERTY_HPP