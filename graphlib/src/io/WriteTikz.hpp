#ifndef GL_WRITE_TIKZ_HPP
#define GL_WRITE_TIKZ_HPP

#include "../structures/Graph.hpp"
#include <iostream>

namespace gl {
namespace external {

/**
 * @brief Write structure to stream, given 
 * @param s stream to which it should write
 * @param g A gl::Graph compatible graph.
 * @param writeNodes whether the nodes shall be labeled (numbers)
 * @param writeEdgeWeights whether the edges shall be labeled (weights)
 */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void writeTikzNetwork(std::ostream &s, Graph<SCALAR, STORAGE_KIND, DIRECTION> &g, bool writeNodes = true, bool writeEdgeWeights = true)
{
  s << "\\RequirePackage{luatex85}" << std::endl;
  s << "\\documentclass{standalone}" << std::endl;
  s << "\\usepackage{tikz-network}" << std::endl;
  s << "\\begin{document}" << std::endl;
  s << "\\begin{tikzpicture}" << std::endl;

  for (gl::index_type i = 0; i < g.numNodes(); i++)
  {
    auto color = g.getNodeColor(i);
    s << "  \\Vertex[x=" << g.getNodePosition(i).first << ",y=" << g.getNodePosition(i).second
      << ",RGB,color={" << +color.r() << "," << +color.g()
      << "," << +color.b() << "},opacity=" << +color.a()
      << ",size=" << g.getNodeCapacity(i); // idea: set to capacity of vertex
    if (g.getNodeLabel(i) == "")
    {
      s << ",IdAsLabel";
    }
    else
    {
      s << ",label=" << g.getNodeLabel(i) << ",position=above";
    }
    s << (writeNodes ? "" : ",NoLabel")
      << "]{" << i << "}" << std::endl;
  }
  s << "\n";

  // draw all edges
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    if ((std::is_same_v<DIRECTION, gl::Undirected> && it->source() <= it->dest()) || std::is_same_v<DIRECTION, gl::Directed>)
    {
      auto color = it->color();
      s << "  \\Edge[" << (g.isDirected() ? "Direct," : "")
        << (it->source() == it->dest() ? "loopshape=45," : "")
        << "RGB,color={" << +color.r() << "," << +color.g()
        << "," << +color.b() << "},opacity=" << +color.a();
      if (writeEdgeWeights)
      {
        s << ",label=" << it->weight();
      }
      s << "](" << it->source() << ")(" << it->dest() << ")" << std::endl;
    }
  }
  s << "\\node[above,align=center,font=\\bfseries] at (current bounding box.north) {" << g.getGraphLabel() << "};" << std::endl;
  s << "\\end{tikzpicture}" << std::endl;
  s << "\\end{document}" << std::endl;
}

} // namespace external
} // namespace gl

#endif // GL_WRITE_TIKZ_HPP