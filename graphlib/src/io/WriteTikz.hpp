#ifndef GL_WRITE_TIKZ_HPP
#define GL_WRITE_TIKZ_HPP

#include "../structures/Graph.hpp"
#include <iostream>
#include <Eigen/Dense>

namespace gl
{

/**
   @brief Simple function, writes structure to the given stream,
   which then can be runned through pdflatex to generate a pdf.
   */
template <class SCALAR>
void writeTikzToStream(std::ostream &s, Graph<SCALAR> &g)
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
                    s << "\\Loop[dist=4cm,dir=NO,label=" << g.getWeight(i, j) << "](" << i << ".west)\n";
                }
                else
                {
                    s << "\\Edge[label=" << g.getWeight(i, j) << "](" << i << ")(" << j << ")\n";
                }
            }
        }
    }

    s << "\\end{tikzpicture}\n\\end{document}" << std::endl;
}

/**
   @brief Write structure to stream
   @param s stream to which it should write
   @param g should be a undirected graph, with at least 2 nodes
   @param writeNodes wheter it should write nodes (numbers)
   */
template <class SCALAR>
void writeTikzToStream2(std::ostream &s, Graph<SCALAR> &g, bool writeNodes = true)
{
    s << "\\documentclass{amsart}" << std::endl;
    s << "\\usepackage{tikz}" << std::endl;
    s << "\\begin{document}" << std::endl;
    s << "\\begin{center}" << std::endl;
    s << "\\begin{tikzpicture}" << std::endl;

    // draw all vertices

    // calculate x,y positions
    using E_MAT = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
    Eigen::Matrix<double, Eigen::Dynamic, 1> degs(g.numNodes());
    E_MAT adjMat(g.numNodes(), g.numNodes());
    E_MAT degMat;

    degMat.setZero();
    adjMat.setZero();

    // build degree matrix
    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        degs(i) = g.getDegree(i);
    }
    degMat = degs.asDiagonal();

    // build adjacency matrix
    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        typename Graph<SCALAR>::idx_list_t neighbours = g.getNeighbours(i);
        for (auto n : neighbours)
        {
            adjMat(i, n) = 1;
            adjMat(n, i) = 1; // undirected
        }
    }

    E_MAT laplacian = degMat - adjMat;

    // calculate eigen vectors
    Eigen::EigenSolver<E_MAT> solver;
    solver.compute(laplacian);

    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        Eigen::Vector2d pos;
        pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

        // Scale by degree
        pos.normalize();
        pos *= (1 + g.getDegree(i));

        s << "  \\node (" << i << ") at (" << pos(0) << ", "
          << pos(1) << ") {";
        if (writeNodes)
            s << i;
        s << "};" << std::endl;
    }

    // draw all edges
    s << "  \\begin{scope}[every path/.style={->}]" << std::endl;
    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        typename Graph<SCALAR>::idx_list_t neighbours = g.getNeighbours(i);
        for (auto n : neighbours)
        {
            if (i == n)
                continue; // removing circle to itself
            s << "    \\draw (" << i << ") -- (" << n << ");" << std::endl;
        }
    }

    s << "  \\end{scope}" << std::endl;
    s << "\\end{tikzpicture}" << std::endl;
    s << "\\end{center}" << std::endl;
    s << "\\end{document}" << std::endl;
}

} /* namespace gl */

#endif /* GL_WRITE_TIKZ_HPP */