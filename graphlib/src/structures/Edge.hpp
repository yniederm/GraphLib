#ifndef GL_EDGE_HPP
#define GL_EDGE_HPP

#include "Color.hpp"

namespace gl {

///////////////////////////////////////////////////////////
//    Edge Class declaration
///////////////////////////////////////////////////////////

/** 
 * @class Edge
 * @brief Represents an Edge in a Graph.
 * @tparam SCALAR Number type used to store edge weights.
 */
template <class SCALAR = int>
class Edge
{
public:
  using val_t = SCALAR;             ///< Value type
  using idx_t = gl::index_type;     ///< Index type
  /**
   * @brief Construct Edge from data
   * @param[in] src Source index
   * @param[in] dest Destination index
   * @param[in] weight The weight of the %Edge
   * @param[in] color Color of the %Edge
   * @param[in] exists Whether the %Edge exists
   */
  Edge(const idx_t &src = 0, const idx_t &dest = 0, const val_t &weight = 0, const Color &color = Color("black"), const bool &exists = false) : src_(src), dest_(dest), weight_(weight), exists_(exists), color_(color) {}

  Edge(const Edge<SCALAR>&) = default;                ///< @brief Copy constructor
  Edge(Edge<SCALAR>&&) noexcept = default;            ///< @brief Move constructor
  Edge &operator=(const Edge<SCALAR>&) = default;     ///< @brief Copy assignment
  Edge &operator=(Edge<SCALAR>&&) noexcept = default; ///< @brief Move assignment
  ~Edge() = default;                            ///< @brief Destructor


  /**
   * @brief Check whether two edges are equal.
   * @return true if equal, false otherwise.
   */
  bool operator== (const Edge& rhs) const;
  /**
   * @brief Check whether two edges are not equal.
   * @return true if not equal, false otherwise.
   */
  bool operator!= (const Edge& rhs) const;

  /**
   * @name exists
   * @brief Access to boolean value exists.
   * This signifies the existance of an edge in the graph.
   */
  //@{
  /**
   * @brief Checks whether an edge exists.
   * @return True if exists, false otherwise.
   */
  inline bool exists() const;
  /**
   * @brief Allows changing of existance status of an edge.
   * @param[in] exists New value of boolean exists.
   */
  inline void exists(bool exists);
  //@}
  /**
   * @name source
   * @brief Access to index of source node.
   */
  //@{
  /**
   * @brief Gets the index of the source of the edge.
   * @return index of edge source node.
   */
  inline idx_t source() const;
  /**
   * @brief Allows changing the source of an edge.
   * @param[in] src New value of source index.
   */
  inline void source(idx_t src);
  //@}
  /**
   * @name dest
   * @brief Access to index of destination node.
   */
  //@{
  /**
   * @brief Gets the index of the destination of the edge.
   * @return index of edge destination node.
   */
  inline idx_t dest() const;
  /**
   * @brief Allows changing the destination of an edge.
   * @param[in] dest New value of destination index.
   */
  inline void dest(idx_t dest);
  //@}
  /**
   * @name weight
   * @brief Access to weight of the edge.
   */
  //@{
  /**
   * @brief Gets the weight of the edge.
   * @return Weight of the edge.
   */
  inline val_t weight() const;
  /**
   * @brief Allows changing the weight of an edge.
   * @param[in] weight New value of edge weight.
   */
  inline void weight(val_t weight);
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

private:
  idx_t src_;    ///< @brief Source index
  idx_t dest_;   ///< @brief Destination index
  val_t weight_; ///< @brief Edge weight
  bool exists_;  ///< @brief Edge existance
  Color color_;  ///< @brief Edge color
};

///////////////////////////////////////////////////////////
//    Edge function implementations
///////////////////////////////////////////////////////////

// equality operator
template <class SCALAR>
bool Edge<SCALAR>::operator== (const Edge<SCALAR>& rhs) const
{
  return src_ == rhs.src_ 
      && dest_ == rhs.dest_
      && weight_ == rhs.weight_
      && exists_ == rhs.exists_
      && color_ == rhs.color_;
}
// inequality operator
template <class SCALAR>
bool Edge<SCALAR>::operator!= (const Edge<SCALAR>& rhs) const
{
  return !operator==(rhs);
}

// getter for exists
template <class SCALAR>
inline bool Edge<SCALAR>::exists() const {
  return exists_;
}

// setter for exists
template <class SCALAR>
inline void Edge<SCALAR>::exists(bool exists) {
  exists_ = exists;
}

// getter for src
template <class SCALAR>
inline typename Edge<SCALAR>::idx_t Edge<SCALAR>::source() const {
  return src_;
}
// setter for src
template <class SCALAR>
inline void Edge<SCALAR>::source(idx_t src) {
  src_ = src;
}

// getter for dest
template <class SCALAR>
inline typename Edge<SCALAR>::idx_t Edge<SCALAR>::dest() const {
  return dest_;
}
// setter for dest
template <class SCALAR>
inline void Edge<SCALAR>::dest(idx_t dest) {
  dest_ = dest;
}

// getter for weight
template <class SCALAR>
inline typename Edge<SCALAR>::val_t Edge<SCALAR>::weight() const {
  return weight_;
}
// setter for weight
template <class SCALAR>
inline void Edge<SCALAR>::weight(val_t weight) {
  weight_ = weight;
}

// getter for color object
template <class SCALAR>
inline gl::Color Edge<SCALAR>::color() const {
  return color_;
}
// setter for color object
template <class SCALAR>
inline void Edge<SCALAR>::color(const Color& color) {
  color_ = color;
}

} // namespace gl

#endif // GL_EDGE_HPP