#ifndef GL_NODE_HPP
#define GL_NODE_HPP

#include "Graph.hpp"

namespace gl
{

///////////////////////////////////////////////////////////
//    Graph::Node function implementations
///////////////////////////////////////////////////////////

/* \internal getter for id */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::id() const
{
  return id_;
}

/* \internal setter for id */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::id(const idx_t &id)
{
  id_ = id;
}

/* \internal getter for label */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::label() const
{
  return label_;
}

/* \internal setter for label */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::label(const std::string &label)
{
  label_ = label;
}

/* \internal getter for capacity */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::val_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::capacity() const
{
  return capacity_;
}

/* \internal setter for capacity */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::capacity(const val_t &capacity)
{
  capacity_ = capacity;
}

/* \internal getter for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegree() const
{
  return inDegree_;
}

/* \internal increment for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegreeIncrement(const idx_t &increment)
{
  inDegree_ += increment;
}

/* \internal decrement for inDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegreeDecrement(const idx_t &decrement)
{
  inDegree_ -= decrement;
}

/* \internal getter for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegree() const
{
  return outDegree_;
}

/* \internal increment for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegreeIncrement(const idx_t &increment)
{
  outDegree_++;
}

/* \internal decrement for outDegree */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegreeDecrement(const idx_t &decrement)
{
  outDegree_--;
}

/* \internal getter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline gl::Color Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::color() const
{
  return color_;
}

/* \internal setter for color object */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::color(const Color &color)
{
  color_ = color;
}
/* \internal getter for position */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::pair<float, float> Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::position() const
{
  return position_;
}
/* \internal setter for position */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::position(const std::pair<float, float> &pos)
{
  position_ = pos;
}

} // namespace gl

#endif // GL_NODE_HPP