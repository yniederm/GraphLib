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
  return exists_;
}

/* \internal setter for exists */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::exists(bool exists) {
  exists_ = exists;
}

/* \internal getter for src */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source() const {
  return src_;
}

/* \internal setter for src */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::source(idx_t src) {
  src_ = src;
}

/* \internal getter for dest */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest() const {
  return dest_;
}

/* \internal setter for dest */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::dest(idx_t dest) {
  dest_ = dest;
}

/* \internal getter for weight */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight() const {
  return weight_;
}

/* \internal setter for weight */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::weight(val_t weight) {
  weight_ = weight;
}

/* \internal getter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline gl::Color Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::color() const {
  return color_;
}

/* \internal setter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Edge::color(const Color& color) {
  color_ = color;
}

} // namespace gl

#endif // GL_EDGE_HPP