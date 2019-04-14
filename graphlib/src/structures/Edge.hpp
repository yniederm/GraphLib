#ifndef GL_EDGE_HPP
#define GL_EDGE_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Edge function implementations
///////////////////////////////////////////////////////////

/* \internal */
//@{
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
using idx_t = typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t;
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
using val_t = typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t;
//@}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
bool Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::exists() const {
  return _exists;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::exists(bool exists) {
  _exists = exists;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source() const {
  return _src;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source(idx_t src) {
  _src = src;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest() const {
  return _dest;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest(idx_t dest) {
  _dest = dest;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight() const {
  return _weight;
}

/* \internal */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight(val_t weight) {
  _weight = weight;
}

} // namespace gl

#endif // GL_EDGE_HPP