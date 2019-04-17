#ifndef GL_NODE_HPP
#define GL_NODE_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Node function implementations
///////////////////////////////////////////////////////////

/* \internal getter for id */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::id() const {
  return id_;
}

/* \internal setter for id */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::id(idx_t id) {
  id_ = id;
}

/* \internal getter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::name() const {
  return name_;
}

/* \internal setter for name */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::name(const std::string& name) {
  name_ = name;
}

/* \internal getter for capacity */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::val_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::capacity() const {
  return capacity_;
}

/* \internal setter for weight */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::capacity(val_t weight) {
  capacity_ = capacity;
}

/* \internal getter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline gl::Color Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::color() const {
  return color_;
}

/* \internal setter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::color(const Color& color) {
  color_ = color;
}

/* \internal getter for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::inDegree() const {
  return inDegree_;
}

/* \internal increment for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::inDegreeIncrement() {
  inDegree_++;
}

/* \internal decrement for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::inDegreeDecrement() {
  inDegree_--;
}

/* \internal getter for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR,STORAGE_KIND,DIRECTION>::idx_t Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::outDegree() const {
  return outDegree_;
}

/* \internal increment for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::outDegreeIncrement() {
  outDegree_++;
}

/* \internal decrement for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::outDegreeDecrement() {
  outDegree_--;
}

} // namespace gl

#endif // GL_NODE_HPP