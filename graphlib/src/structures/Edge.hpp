#ifndef GL_EDGE_HPP
#define GL_EDGE_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Edge function implementations
///////////////////////////////////////////////////////////


/* \internal getter for exists */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline bool Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::exists() const {
  return _exists;
}

/* \internal setter for exists */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::exists(bool exists) {
  _exists = exists;
}

/* \internal getter for src */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source() const {
  return _src;
}

/* \internal setter for src */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source(idx_t src) {
  _src = src;
}

/* \internal getter for dest */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest() const {
  return _dest;
}

/* \internal setter for dest */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest(idx_t dest) {
  _dest = dest;
}

/* \internal getter for weight */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight() const {
  return _weight;
}

/* \internal setter for weight */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight(val_t weight) {
  _weight = weight;
}

} // namespace gl

#endif // GL_EDGE_HPP