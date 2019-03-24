#ifndef GL_WRITE_IMAGE_HPP
#define GL_WRITE_IMAGE_HPP

#include "../structures/Graph.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <mgl2/mgl.h>

namespace gl
{

/**
   @brief Plot graph using mgl2
   @param gr Pointer to mglGraph
   @param g the graph to plot
   @param lineArgs arguments for plotting the lines
   */
template <class SCALAR>
void saveImage(mglGraph* gr, gl::Graph<SCALAR> &g, const char* lineArgs = "B")
{
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

    Eigen::MatrixXd positions(2, g.numNodes());

    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        Eigen::Vector2d pos;
        pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

        // Scale by degree
        pos.normalize();
        pos *= (1 + g.getDegree(i));

        positions.col(i) = pos;
    }

    // set plot ranges
    gr->SetRange('x', positions.row(0).minCoeff(), positions.row(0).maxCoeff());
    gr->SetRange('y', positions.row(1).minCoeff(), positions.row(1).maxCoeff());

    // draw all edges
    for (typename Graph<SCALAR>::idx_t i = 0; i < g.numNodes(); i++)
    {
        typename Graph<SCALAR>::idx_list_t neighbours = g.getNeighbours(i);
        for (auto n : neighbours)
        {
            mglPoint p1(positions(0, i), positions(1, i));
            mglPoint p2(positions(0, n), positions(1, n));

            gr->Line(p1, p2, lineArgs);
        }
    }
}

} /* namespace gl */

#endif /* GL_WRITE_IMAGE_HPP */