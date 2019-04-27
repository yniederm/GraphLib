#ifndef GL_WRITE_TIKZ_HPP
#define GL_WRITE_TIKZ_HPP

#include "../structures/Graph.hpp"
#include <iostream>
#include <Eigen/Dense>

namespace gl
{
namespace external
{

/**
   @brief Simple function, writes structure to the given stream,
   which then can be run through pdflatex to generate a pdf.
   */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void writeTikzToStream(std::ostream &s, Graph<SCALAR, STORAGE_KIND, DIRECTION> &g)
{
  s << "\\documentclass[border=10pt]{standalone}\n"
    << "\\usepackage{tkz-graph}\n"
    << "\\GraphInit[vstyle = Shade]\n"
    << "\\tikzset{\n"
    << "  LabelStyle/.style = { rectangle, rounded corners, draw,\n"
    << "      fill = yellow!50, text = red, font = \\bfseries },\n"
    << "  VertexStyle/.append style = { inner sep=2pt,\n"
    << "      font = \\Large\\bfseries},\n"
    << "  EdgeStyle/.append style = {->, bend left} }\n"
    << "\\thispagestyle{empty}\n"
    << "\\begin{document}\n"
    << "\\begin{tikzpicture}\n"
    << "\\SetGraphUnit{2}\n";
  for (int i = 0; i < g.numNodes(); i++)
  {
    if (i == 0)
      s << "\\Vertex{" << i << "}" << std::endl;
    else
      s << "\\WE(" << i - 1 << "){" << i << "}" << std::endl;
  }

  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    if (it->source() == it->dest())
    {
      s << "\\Loop[dist=4cm,dir=NO,label=" << it->weight() << "](" << it->source() << ".west)\n";
    }
    else
    {
      s << "\\Edge[label=" << it->weight() << "](" << it->source() << ")(" << it->dest() << ")\n";
    }
  }

  s << "\\end{tikzpicture}\n\\end{document}" << std::endl;
}

/**
   @brief Write structure to stream, given 
   @param s stream to which it should write
   @param g should be a undirected graph, with at least 2 nodes
   @param useInternalPositions if this function should use the internal node positions initialized
   @param writeNodes wheter it should write nodes (numbers)
   */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void writeTikzToStream2(std::ostream &s, Graph<SCALAR, STORAGE_KIND, DIRECTION> &g, bool useInternalPositions = false, bool writeNodes = true)
{
  s << "\\documentclass{standalone}" << std::endl;
  s << "\\usepackage{tikz-network}" << std::endl;
  s << "\\begin{document}" << std::endl;
  s << "\\begin{tikzpicture}" << std::endl;

  // draw all vertices
  if (!useInternalPositions)
  {
    // calculate x,y positions
    using E_MAT = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
    Eigen::Matrix<float, Eigen::Dynamic, 1> degs(g.numNodes());
    E_MAT adjMat(g.numNodes(), g.numNodes());
    E_MAT degMat;

    degMat.setZero();
    adjMat.setZero();

    // build degree matrix
    for (typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
    {
      degs(i) = g.getNodeDegree(i);
    }
    degMat = degs.asDiagonal();

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
      adjMat(it->source(), it->dest()) = 1;
      adjMat(it->dest(), it->source()) = 1;
    }

    E_MAT laplacian = degMat - adjMat;

    // calculate eigen vectors
    Eigen::EigenSolver<E_MAT> solver;
    solver.compute(laplacian);

    for (typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
    {
      Eigen::Vector2d pos;
      pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

      // Scale by degree
      pos.normalize();
      pos *= (1 + g.getNodeDegree(i));
      auto color = g.getNodeColor(i);

      s << "  \\Vertex[x=" << pos(0) << ",y=" << pos(1)
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
      s << (writeNodes ? "" : ",Pseudo")
        << "]{" << i << "}" << std::endl;
    }
  }
  else
  {

    // use internal positions
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
      s << (writeNodes ? "" : ",Pseudo")
        << "]{" << i << "}" << std::endl;
    }
  }

  // draw all edges
  // s << "  \\begin{scope}[every path/.style={->}]" << std::endl;
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    auto color = it->color();
    s << "    \\Edge[" << (g.isDirected() ? "Direct," : "")
      << (it->source() == it->dest() ? "loopshape=45," : "")
      << "RGB,color={" << +color.r() << "," << +color.g()
      << "," << +color.b() << "},opacity=" << +color.a()
      << ",label=" << it->weight() << "](" << it->source() << ")(" << it->dest() << ")" << std::endl;
  }

  // s << "  \\end{scope}" << std::endl;
  s << "\\node[align=center,font=\\bfseries] at (current bounding box.north) {" << g.getGraphLabel() << "};" << std::endl;
  s << "\\end{tikzpicture}" << std::endl;
  s << "\\end{document}" << std::endl;
}

} /* namespace external */
} /* namespace gl */

#endif /* GL_WRITE_TIKZ_HPP */