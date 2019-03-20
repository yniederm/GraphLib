#ifndef GL_WRITE_TIKZ_HPP
#define GL_WRITE_TIKZ_HPP

#include "../structures/Graph.hpp"
#include <iostream>

namespace gl
{

/**
   @brief Simple function, writes structure to the given stream,
   which then can be runned through pdflatex to generate a pdf.
   */
template <class SCALAR>
void writeTikzToStream(std::ostream& s, gl::Graph<SCALAR> &g)
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

    for (int i = 0; i < g.numNodes(); i++)
    {
        for (int j = 0; j < g.numNodes(); j++)
        {
            if (g.hasEdge(i, j))
            {
                if (i == j)
                {
                    s << "\\Loop[dist=4cm,dir=NO,label=" << g.getWeight(i,j) << "](" << i << ".west)\n";
                }
                else
                {
                    s << "\\Edge[label=" << g.getWeight(i,j) << "](" << i << ")(" << j << ")\n";
                }
            }
        }
    }

    s << "\\end{tikzpicture}\n\\end{document}" << std::endl;
}

} /* namespace gl */

#endif /* GL_WRITE_TIKZ_HPP */