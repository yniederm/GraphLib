#ifndef GL_NODE_HPP
#define GL_NODE_HPP

#include "Graph.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Graph::Node function implementations
///////////////////////////////////////////////////////////

// equality operator
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
bool Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::operator== (const Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node& rhs) const
{
  return id_ == rhs.id_ 
      && label_ == rhs.label_
      && capacity_ == rhs.capacity_
      && color_ == rhs.color_
      && inDegree_ == rhs.inDegree_
      && outDegree_ == rhs.outDegree_
      && position_ == rhs.position_;
}
// inequality operator
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
bool Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node::operator!= (const Graph<SCALAR,STORAGE_KIND,DIRECTION>::Node& rhs) const
{
  return !operator!=(rhs);
}

// getter for id
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::id() const
{
  return id_;
}
// setter for id
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::id(const idx_t &id)
{
  id_ = id;
}

// getter for label
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::string Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::label() const
{
  return label_;
}
// setter for label
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::label(const std::string &label)
{
  label_ = label;
}

// getter for capacity
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::val_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::capacity() const
{
  return capacity_;
}
// setter for capacity
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::capacity(const val_t &capacity)
{
  capacity_ = capacity;
}

// getter for inDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegree() const
{
  return inDegree_;
}
// increment for inDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegreeIncrement(const idx_t &increment)
{
  inDegree_ += increment;
}
// decrement for inDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::inDegreeDecrement(const idx_t &decrement)
{
  inDegree_ -= decrement;
}

// getter for outDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegree() const
{
  return outDegree_;
}
// increment for outDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegreeIncrement(const idx_t &increment)
{
  outDegree_++;
}
// decrement for outDegree
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::outDegreeDecrement(const idx_t &decrement)
{
  outDegree_--;
}

// getter for color object
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline gl::Color Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::color() const
{
  return color_;
}
// setter for color object
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::color(const Color &color)
{
  color_ = color;
}

// getter for position
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline std::pair<float, float> Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::position() const
{
  return position_;
}
// setter for position
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
inline void Graph<SCALAR, STORAGE_KIND, DIRECTION>::Node::position(const std::pair<float, float> &pos)
{
  position_ = pos;
}

} // namespace gl

#endif // GL_NODE_HPP