#ifndef GL_PROPERTY_HPP
#define GL_PROPERTY_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Property function implementations
///////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* \internal getter for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodes() const {
  return numNodes_;
}

/* \internal setter for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodes(const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& numNodes) {
  numNodes_ = numNodes;
}

/* \internal increment for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesIncrement (const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& increment) {
  numNodes_ += increment;
}
/* \internal decrement for numNodes */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numNodesDecrement (const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& decrement) {
  numNodes_ -= decrement;
}

/* \internal getter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges() const {
  return numEdges_;
}

/* \internal setter for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdges(const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& numEdges) {
  numEdges_ = numEdges;
}

/* \internal increment for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesIncrement (const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& increment) {
  numEdges_ += increment;
}
/* \internal decrement for numEdges */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::numEdgesDecrement (const typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t& decrement) {
  numEdges_ -= decrement;
}
/* \internal getter for label */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::label() const {
  return label_;
}

/* \internal setter for label */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Property::label(const std::string& label) {
  label_ = label;
}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace gl

#endif // GL_PROPERTY_HPP