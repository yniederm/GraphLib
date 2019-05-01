#ifndef GL_UPDATE_FLAGGED_COMPONENTS_HPP
#define GL_UPDATE_FLAGGED_COMPONENTS_HPP

namespace gl::interface 
{

/**
 * @brief Colors edges selectively using a selector function.
 * @tparam SELECTOR Selector Object: Colors exactly those edges that are "selected".
 * @tparam GRAPH Graph Object.
 * @param[in] graph Reference to graph that needs to be modified.
 * @param[in] selector Reference to selector object
 */
template <class SELECTOR, class GRAPH>
void colorFlaggedEdges (GRAPH& graph, SELECTOR&& selector)
{
  for (auto edge = graph.edge_begin(); edge != graph.edge_end(); ++edge)
  {
    const auto selectedVal = selector(edge->source(), edge->dest());
    if (selectedVal.first) 
    {
      edge->color(selectedVal.second);
    }
  }
}
/**
 * @brief Colors nodes selectively using a selector function.
 * @tparam SELECTOR Selector Object: Colors exactly those nodes that are "selected".
 * @tparam GRAPH Graph Object.
 * @param[in] graph Reference to graph that needs to be modified.
 * @param[in] selector Reference to selector object
 */
template <class SELECTOR, class GRAPH>
void colorFlaggedNodes (GRAPH& graph, SELECTOR&& selector)
{
  for (auto node = graph.node_begin(); node != graph.node_end(); ++node)
  {
    const auto selectedVal = selector(node->id());
    if (selectedVal.first) 
    {
      node->color(selectedVal.second);
    }
  }
}
/**
 * @brief Colors nodes & edges selectively using a selector function.
 * @tparam EDGE_SELECTOR Selector Object: Colors exactly those edges that are "selected".
 * @tparam NODE_SELECTOR Selector Object: Colors exactly those nodes that are "selected".
 * @tparam GRAPH Graph Object.
 * @param[in] graph Reference to graph that needs to be modified.
 * @param[in] edge_selector Reference to selector object for edges
 * @param[in] node_selector Reference to selector object for nodes
 */
template <class EDGE_SELECTOR, class NODE_SELECTOR, class GRAPH>
void colorFlaggedEntities (GRAPH& graph, EDGE_SELECTOR&& edge_selector, NODE_SELECTOR&& node_selector)
{
  gl::interface::colorFlaggedEdges(graph,edge_selector);
  gl::interface::colorFlaggedNodes(graph,node_selector);
}

} // namespace gl::interface

#endif // GL_UPDATE_FLAGGED_COMPONENTS_HPP