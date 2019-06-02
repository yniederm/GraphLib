#ifndef GL_PROPERTY_HPP
#define GL_PROPERTY_HPP

namespace gl {

///////////////////////////////////////////////////////////
//    Property Class declaration
///////////////////////////////////////////////////////////

/** 
 * @class Property
 * @brief Stores the properties of a Graph.
 */
class Property
{
public:
  using idx_t = gl::index_type;

  Property(const idx_t &numNodes = 0, const std::string &label = "Graph") : numNodes_(numNodes), label_(label), numEdges_(0) {}

  Property(const Property&) = default;                ///< @brief Copy constructor
  Property(Property&&) noexcept = default;            ///< @brief Move constructor
  Property &operator=(const Property&) = default;     ///< @brief Copy assignment
  Property &operator=(Property&&) noexcept = default; ///< @brief Move assignment
  ~Property() = default;                            ///< @brief Destructor

  /**
   * @brief Check whether two propertes are equal.
   * @return true if equal, false otherwise.
   */
  bool operator== (const Property& rhs) const;
  /**
   * @brief Check whether two propertes are not equal.
   * @return true if not equal, false otherwise.
   */
  bool operator!= (const Property& rhs) const;
  /**
   * @name numNodes
   * @brief Access to the number of nodes in the graph.
   */
  //@{
  /**
   * @brief Gets the number of nodes in the graph.
   * @return Number of nodes in the graph.
   */
  inline idx_t numNodes() const;
  /**
   * @brief Allows changing the number of nodes in the graph.
   * @param[in] numNodes New value of node count.
   */
  inline void numNodes(const idx_t &numNodes);
  /**
   * @brief Increments the number of nodes in the graph.
   * @param[in] increment Number of nodes that will be added to the graph.
   */
  inline void numNodesIncrement(const idx_t &increment = 1);
  /**
   * @brief Decrements the number of nodes in the graph.
   * @param[in] decrement Number of nodes that will be removed from the graph.
   */
  inline void numNodesDecrement(const idx_t &decrement = 1);
  //@}
  /**
   * @name numEdges
   * @brief Access to the number of edges in the graph.
   */
  //@{
  /**
   * @brief Gets the number of edges in the graph.
   * @return Number of edges in the graph.
   */
  inline idx_t numEdges() const;
  /**
   * @brief Allows changing the number of edges in the graph.
   * @param[in] numEdges New value of edge count.
   */
  inline void numEdges(const idx_t &numEdges);
  /**
   * @brief Increments the number of edges in the graph.
   * @param[in] increment Number of nodes that will be added to the graph.
   */
  inline void numEdgesIncrement(const idx_t &increment = 1);
  /**
   * @brief Decrements the number of edges in the graph.
   * @param[in] decrement Number of edges that will be removed from the graph.
   */
  inline void numEdgesDecrement(const idx_t &decrement = 1);
  //@}
  /**
   * @name Label
   * @brief Access to label of the graph.
   */
  //@{
  /**
   * @brief Gets the label of the graph.
   * @return Graph name.
   */
  inline std::string label() const;
  /**
   * @brief Allows changing the label of the graph.
   * @param[in] label New graph name.
   */
  inline void label(const std::string &label);
  //@}

private:
  idx_t numNodes_;    ///< @brief Number of nodes in the graph
  idx_t numEdges_;    ///< @brief Number of edges in the graph
  std::string label_; ///< @brief Label of the graph
};

///////////////////////////////////////////////////////////
//    Property function implementations
///////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// equality operator
bool Property::operator== (const Property& rhs) const
{
  return numNodes_ == rhs.numNodes_ 
      && numEdges_ == rhs.numEdges_
      && label_ == rhs.label_;
}
// inequality operator
bool Property::operator!= (const Property& rhs) const
{
  return !operator==(rhs);
}

// getter for numNodes
inline typename Property::idx_t Property::numNodes() const {
  return numNodes_;
}
// setter for numNodes
inline void Property::numNodes(const typename Property::idx_t& numNodes) {
  numNodes_ = numNodes;
}

// increment for numNodes
inline void Property::numNodesIncrement (const typename Property::idx_t& increment) {
  numNodes_ += increment;
}
// decrement for numNodes
inline void Property::numNodesDecrement (const typename Property::idx_t& decrement) {
  GL_ASSERT(decrement <= numNodes_,"Property::numNodesDecrement | Decrement results in negative number of nodes")
  numNodes_ -= decrement;
}

// getter for numEdges
inline typename Property::idx_t Property::numEdges() const {
  return numEdges_;
}
// setter for numEdges
inline void Property::numEdges(const typename Property::idx_t& numEdges) {
  numEdges_ = numEdges;
}

// increment for numEdges
inline void Property::numEdgesIncrement (const typename Property::idx_t& increment) {
  numEdges_ += increment;
}
// decrement for numEdges
inline void Property::numEdgesDecrement (const typename Property::idx_t& decrement) {GL_ASSERT(decrement <= numNodes_,"Property::numEdgesDecrement | Decrement results in negative number of edges")
  numEdges_ -= decrement;
}

// getter for label
inline std::string Property::label() const {
  return label_;
}
// setter for label
inline void Property::label(const std::string& label) {
  label_ = label;
}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

} // namespace gl

#endif // GL_PROPERTY_HPP