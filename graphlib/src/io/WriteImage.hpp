#ifndef GL_WRITE_IMAGE_HPP
#define GL_WRITE_IMAGE_HPP

#include "../structures/Graph.hpp"
#include "../algorithms/SpectralPlacing.hpp"
#include "../algorithms/LaplacianSTL.hpp"
#include <iostream>
#include <vector>
#include <mgl2/mgl.h>

namespace gl
{
namespace external
{

/**
 * @brief Plot graph using mgl2
 * @param gr Pointer to mglGraph
 * @param g the graph to plot
 * @param lineArgs arguments for plotting the lines
 */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void saveImage(mglGraph *gr, gl::Graph<SCALAR, STORAGE_KIND, DIRECTION> &g, const char *lineArgs = "")
{
  // calculate spectral placing
  gl::algorithm::SpectralPlacing(g);

  float minX = g.getNodePosition(0).first;
  float maxX = g.getNodePosition(0).first;
  float minY = g.getNodePosition(0).second;
  float maxY = g.getNodePosition(0).second;

  for (auto it = g.node_cbegin(); it != g.node_cend(); it++)
  {
    if (g.getNodePosition(it->id()).first < minX)
      minX = g.getNodePosition(it->id()).first;
    if (g.getNodePosition(it->id()).first > maxX)
      maxX = g.getNodePosition(it->id()).first;
    if (g.getNodePosition(it->id()).second < minY)
      minY = g.getNodePosition(it->id()).second;
    if (g.getNodePosition(it->id()).second > maxY)
      maxY = g.getNodePosition(it->id()).second;
  }

  // set plot ranges
  gr->SetRange('x', minX, maxX);
  gr->SetRange('y', minY, maxY);

  // draw all edges
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {

    mglPoint p1(g.getNodePosition(it->source()).first, g.getNodePosition(it->source()).second);
    mglPoint p2(g.getNodePosition(it->dest()).first, g.getNodePosition(it->dest()).second);
    std::string output_args = lineArgs;
    output_args += "{x" + it->color().RGB() + "}";

    gr->Line(p1, p2, output_args.data());
  }
}

} // namespace external
} // namespace gl

#endif // GL_WRITE_IMAGE_HPP