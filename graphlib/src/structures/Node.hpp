#ifndef GL_NODE_HPP
#define GL_NODE_HPP

#include "Color.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Node Class declaration
///////////////////////////////////////////////////////////

/** 
 * @class Node
 * @brief Represents a Node in a Graph.
 * @tparam SCALAR Number type used to store node capacities.
 */
template <class SCALAR>
class Node
{
public:
  using val_t = SCALAR;            ///< Value type
  using idx_t = gl::index_type;    ///< Index type

  Node(const idx_t &id = 0, const val_t &capacity = 1, const gl::Color& color = Color("white"), const std::string &label = "", const float& x = 0., const float& y = 0.) : id_(id), label_(label), capacity_(capacity),
                                          color_(color), inDegree_(0), outDegree_(0),
                                          position_(std::make_pair(x,y)) {}

  Node(const Node<SCALAR>&) = default;                ///< @brief Copy constructor
  Node(Node<SCALAR>&&) noexcept = default;            ///< @brief Move constructor
  Node &operator=(const Node<SCALAR>&) = default;     ///< @brief Copy assignment
  Node &operator=(Node<SCALAR>&&) noexcept = default; ///< @brief Move assignment
  ~Node() = default;                            ///< @brief Destructor

  /**
   * @brief Check whether two nodes are equal.
   * @return true if equal, false otherwise.
   */
  bool operator== (const Node& rhs) const;
  /**
   * @brief Check whether two nodes are not equal.
   * @return true if not equal, false otherwise.
   */
  bool operator!= (const Node& rhs) const;

  /**
   * @name id
   * @brief Access to node ID.
   */
  //@{
  /**
   * @brief Checks whether an edge exists.
   * @return True if exists, false otherwise.
   */
  inline idx_t id() const;
  /**
   * @brief Allows changing of node ID.
   * @param[in] id New value of node ID.
   */
  inline void id(const idx_t &id);
  //@}
  /**
   * @name name
   * @brief Access to the label of a node.
   */
  //@{
  /**
   * @brief Gets the label of a node.
   * @return label of the node.
   */
  inline std::string label() const;
  /**
   * @brief Allows changing the label of a node.
   * @param[in] label New value of node label.
   */
  inline void label(const std::string &label);
  //@}
  /**
   * @name capacity
   * @brief Access to capacity of the edge.
   */
  //@{
  /**
   * @brief Gets the capacity of the node.
   * @return Capacity of the node.
   */
  inline val_t capacity() const;
  /**
   * @brief Allows changing the capacity of a node.
   * @param[in] capacity New value of node capacity.
   */
  inline void capacity(const val_t &capacity);
  //@}
  /**
   * @name color
   * @brief Access to the edge's RGBA color value.
   */
  //@{
  /**
   * @brief Gets the edge's color.
   * @return Color of the edge.
   */
  inline Color color() const;
  /**
   * @brief Allows changing the edge's RGBA color value.
   * @param[in] color New color object. 
   */
  inline void color(const Color &color);
  //@}
  /**
   * @name inDegree
   * @brief Access to node in-degree.
   */
  //@{
  /**
   * @brief Gets the in-degree of a node.
   * @return In-degree of a node.
   */
  inline idx_t inDegree() const;
  /**
   * @brief Increments the node in-degree.
   * @param[in] increment number that will be added
   */
  inline void inDegreeIncrement(const idx_t &increment = 1);
  /**
   * @brief Decrements the node in-degree.
   * @param[in] decrement number that will be subtracted
   */
  inline void inDegreeDecrement(const idx_t &decrement = 1);
  //@}
  /**
   * @name outDegree
   * @brief Access to node out-degree.
   */
  //@{
  /**
   * @brief Gets the out-degree of a node.
   * @return Out-degree of a node.
   */
  inline idx_t outDegree() const;
  /**
   * @brief Increments the node out-degree.
   * @param[in] increment number that will be added
   */
  inline void outDegreeIncrement(const idx_t &increment = 1);
  /**
   * @brief Decrements the node out-degree.
   * @param[in] decrement number that will be subtracted
   */
  inline void outDegreeDecrement(const idx_t &decrement = 1);
  //@}
  //@{
  /**
   * @name position
   * @brief Access to node position.
   */
  /**
   * @brief Get Position of this node
   * @return Position of node
   */
  inline std::pair<float, float> position() const;
  /**
   * @brief Set Position of node
   * @param pos The position of the node
   */
  inline void position(const std::pair<float, float> &pos);
  //@}

private:
  idx_t id_;                         ///< @brief Node ID */
  std::string label_;                ///< @brief Node label */
  val_t capacity_;                   ///< @brief Node capacity */
  Color color_;                      ///< @brief Node color */
  idx_t inDegree_;                   ///< @brief In-degree */
  idx_t outDegree_;                  ///< @brief Out-degree */
  std::pair<float, float> position_; ///< @brief Position of node
};

///////////////////////////////////////////////////////////
//    Node function implementations
///////////////////////////////////////////////////////////

// equality operator
template <class SCALAR>
bool Node<SCALAR>::operator== (const Node<SCALAR>& rhs) const
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
template <class SCALAR>
bool Node<SCALAR>::operator!= (const Node<SCALAR>& rhs) const
{
  return !operator==(rhs);
}

// getter for id
template <class SCALAR>
inline typename Node<SCALAR>::idx_t Node<SCALAR>::id() const
{
  return id_;
}
// setter for id
template <class SCALAR>
inline void Node<SCALAR>::id(const idx_t &id)
{
  id_ = id;
}

// getter for label
template <class SCALAR>
inline std::string Node<SCALAR>::label() const
{
  return label_;
}
// setter for label
template <class SCALAR>
inline void Node<SCALAR>::label(const std::string &label)
{
  label_ = label;
}

// getter for capacity
template <class SCALAR>
inline typename Node<SCALAR>::val_t Node<SCALAR>::capacity() const
{
  return capacity_;
}
// setter for capacity
template <class SCALAR>
inline void Node<SCALAR>::capacity(const val_t &capacity)
{
  capacity_ = capacity;
}

// getter for inDegree
template <class SCALAR>
inline typename Node<SCALAR>::idx_t Node<SCALAR>::inDegree() const
{
  return inDegree_;
}
// increment for inDegree
template <class SCALAR>
inline void Node<SCALAR>::inDegreeIncrement(const idx_t &increment)
{
  inDegree_ += increment;
}
// decrement for inDegree
template <class SCALAR>
inline void Node<SCALAR>::inDegreeDecrement(const idx_t &decrement)
{
  GL_ASSERT(decrement <= inDegree_,"Node::inDegreeDecrement | Decrement results in negative inDegree")
  inDegree_ -= decrement;
}

// getter for outDegree
template <class SCALAR>
inline typename Node<SCALAR>::idx_t Node<SCALAR>::outDegree() const
{
  return outDegree_;
}
// increment for outDegree
template <class SCALAR>
inline void Node<SCALAR>::outDegreeIncrement(const idx_t &increment)
{
  outDegree_ += increment;
}
// decrement for outDegree
template <class SCALAR>
inline void Node<SCALAR>::outDegreeDecrement(const idx_t &decrement)
{
  GL_ASSERT(decrement <= outDegree_,"Node::outDegreeDecrement | Decrement results in negative outDegree")
  outDegree_ -= decrement;
}

// getter for color object
template <class SCALAR>
inline gl::Color Node<SCALAR>::color() const
{
  return color_;
}
// setter for color object
template <class SCALAR>
inline void Node<SCALAR>::color(const Color &color)
{
  color_ = color;
}

// getter for position
template <class SCALAR>
inline std::pair<float, float> Node<SCALAR>::position() const
{
  return position_;
}
// setter for position
template <class SCALAR>
inline void Node<SCALAR>::position(const std::pair<float, float> &pos)
{
  position_ = pos;
}

} // namespace gl

#endif // GL_NODE_HPP