#ifndef GL_ENTITY_SELECTOR_HPP
#define GL_ENTITY_SELECTOR_HPP

#include "../gl_base.hpp"
#include "../structures/Color.hpp"

#include <functional>

namespace gl::interface 
{

/**
 * @brief Provides a Selector Object to color the edges in a given Graph.
 * @tparam GRAPH Some Graph type
 * @param[in] graph Graph that contains edges that are to be colored
 * @param[in] trueColor (optional) New color for the graph edges.
 * @param[in] falseColor (optional) New color for all non-graph edges.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class GRAPH>
std::function<std::pair<bool,gl::Color>(const gl::index_type src, const gl::index_type dest)> getEdgeSelectorFromGraph (const GRAPH& graph,
const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("black"))
{
  return [graph, trueColor, falseColor](const gl::index_type src, const gl::index_type dest) -> std::pair<bool,gl::Color> {
      if (graph.hasEdge(src,dest)) 
      {
        return {true,trueColor};
      }
      else
        return {false,falseColor};
    };
}

/**
 * @brief Provides a Selector Object to color the edges in a given Path.
 * @tparam PATH std::pair<bool,typename Graph::idx_list_t>. A Path type whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] path Path of edges and nodes
 * @param[in] trueColor (optional) New color for the path edges.
 * @param[in] falseColor (optional) New color for all non-path edges.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class PATH>
std::function<std::pair<bool,gl::Color>(const gl::index_type src, const gl::index_type dest)> getEdgeSelectorFromPath (const PATH& path,
const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("black"))
{
  return [path, trueColor, falseColor](const gl::index_type src, const gl::index_type dest) -> std::pair<bool,gl::Color> {

      if (!path.first) return {false,falseColor};
      for (gl::index_type i = 0; i < path.second.size() - 1; i++)
      {
        if (path.second[i] == src && path.second[i+1] == dest) 
          return {true,trueColor};
      }
      return {false,falseColor};
    };
}

/**
 * @brief Provides a Selector Object to color the edges in a Shortest Path.
 * @tparam SHORTEST_PATH_ALGORITHM Shortest Path Algorithm that supports a call to getPath(src,dest) that returns an std::pair<bool,typename Graph::idx_list_t> whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] spa Shortest Path Algorithm (e.g. FloydWarshall, Dijkstra)
 * @param[in] pathSource Start of the shortest path
 * @param[in] pathDest End of the shortest path
 * @param[in] trueColor (optional) New color for the SP edges.
 * @param[in] falseColor (optional) New color for all non-SP edges.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class SHORTEST_PATH_ALGORITHM>
std::function<std::pair<bool,gl::Color>(const gl::index_type src, const gl::index_type dest)> getEdgeSelectorFromShortestPath (SHORTEST_PATH_ALGORITHM& spa, const gl::index_type pathSource, const gl::index_type pathDest, const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("black"))
{
  return [&spa, pathSource, pathDest, trueColor, falseColor](const gl::index_type src, const gl::index_type dest) -> std::pair<bool,gl::Color> {
      auto path = spa.getPath(pathSource,pathDest);
      auto selEdge = getEdgeSelectorFromPath(path,trueColor,falseColor);
      return selEdge(src,dest);
    };
}

/**
 * @brief Provides a Selector Object to color the edges in a Shortest Path Tree.
 * @tparam SHORTEST_PATH_ALGORITHM Shortest Path Algorithm that supports a call to getPath(src,dest) that returns an std::pair<bool,typename Graph::idx_list_t> whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] spa Shortest Path Algorithm (e.g. FloydWarshall, Dijkstra)
 * @param[in] treeSource Source of the shortest path tree
 * @param[in] trueColor (optional) New color for the SPT edges.
 * @param[in] falseColor (optional) New color for all non-SPT edges.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class SHORTEST_PATH_ALGORITHM>
std::function<std::pair<bool,gl::Color>(const gl::index_type src, const gl::index_type dest)> getEdgeSelectorFromShortestPathTree (SHORTEST_PATH_ALGORITHM& spa, const gl::index_type treeSource,
const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("black"))
{
  return [&spa, treeSource, trueColor, falseColor](const gl::index_type src, const gl::index_type dest) -> std::pair<bool,gl::Color> {
        auto spt = spa.getSPT(treeSource);
        auto selEdge = getEdgeSelectorFromGraph(spt,trueColor,falseColor);
        return selEdge(src,dest);
    };
}

/**
 * @brief Provides a Selector Object to color the nodes in a given Path.
 * @tparam PATH std::pair<bool,typename Graph::idx_list_t>. A Path type whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] path Path of edges and nodes
 * @param[in] trueColor (optional) New color for the path nodes.
 * @param[in] falseColor (optional) New color for all non-path nodes.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class PATH>
std::function<std::pair<bool,gl::Color>(const gl::index_type node)> getNodeSelectorFromPath (const PATH& path,
const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("white"))
{
  return [path, trueColor, falseColor](const gl::index_type node) -> std::pair<bool,gl::Color> {

      if (!path.first) return {false,falseColor};
      for (gl::index_type i = 0; i < path.second.size(); i++)
      {
        if (path.second[i] == node)
          return {true,trueColor};
      }
      return {false,falseColor};
    };
}

/**
 * @brief Provides a Selector Object to color the nodes in a Shortest Path.
 * @tparam SHORTEST_PATH_ALGORITHM Shortest Path Algorithm that supports a call to getPath(src,dest) that returns an std::pair<bool,typename Graph::idx_list_t> whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] spa Shortest Path Algorithm (e.g. FloydWarshall, Dijkstra)
 * @param[in] pathSource Start of the shortest path
 * @param[in] pathDest End of the shortest path
 * @param[in] trueColor (optional) New color for the SP nodes.
 * @param[in] falseColor (optional) New color for all non-SP nodes.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class SHORTEST_PATH_ALGORITHM>
std::function<std::pair<bool,gl::Color>(const gl::index_type node)> getNodeSelectorFromShortestPath (SHORTEST_PATH_ALGORITHM& spa,
const gl::index_type pathSource, const gl::index_type pathDest, const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("white"))
{
  return [&spa, pathSource, pathDest, trueColor, falseColor](const gl::index_type node) -> std::pair<bool,gl::Color> {
      auto path = spa.getPath(pathSource,pathDest);
      auto selEdge = getNodeSelectorFromPath(path,trueColor,falseColor);
      return selEdge(node);
    };
}

/**
 * @brief Provides a Selector Object to color the nodes in a Shortest Path Tree.
 * @tparam SHORTEST_PATH_ALGORITHM Shortest Path Algorithm that supports a call to getPath(src,dest) that returns an std::pair<bool,typename Graph::idx_list_t> whose first element contains a boolean value that states path existence, and the second pair element contains a vector of node IDs in the shortest path. 
 * @param[in] spa Shortest Path Algorithm (e.g. FloydWarshall, Dijkstra)
 * @param[in] treeSource Source of the shortest path tree
 * @param[in] trueColor (optional) New color for the SPT nodes.
 * @param[in] falseColor (optional) New color for all non-SPT nodes.
 * @return Selector Object: std::pair<bool,gl::Color>
 */
template <class SHORTEST_PATH_ALGORITHM>
std::function<std::pair<bool,gl::Color>(const gl::index_type node)> getNodeSelectorFromShortestPathTree (SHORTEST_PATH_ALGORITHM& spa, const gl::index_type treeSource,
const gl::Color& trueColor = gl::Color("red"), const gl::Color& falseColor = gl::Color("white"))
{
  return [&spa, treeSource, trueColor, falseColor](const gl::index_type node) -> std::pair<bool,gl::Color> {
        if (!spa.pathLength(treeSource,node).isInfinite())
        {
          return {true,trueColor};
        }
        else
        {
          return {false,falseColor};
        }
    };
}

} // namespace gl::interface

#endif // GL_ENTITY_SELECTOR_HPP