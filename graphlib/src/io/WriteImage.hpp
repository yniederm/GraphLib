#ifndef GL_WRITE_IMAGE_HPP
#define GL_WRITE_IMAGE_HPP

#include "../structures/Graph.hpp"
#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <vector>
#include <mgl2/mgl.h>

namespace gl {
namespace external {

/**
   @brief Plot graph using mgl2
   @param gr Pointer to mglGraph
   @param g the graph to plot
   @param lineArgs arguments for plotting the lines
   */
template <class SCALAR, class DIRECTION>
void saveImage(mglGraph* gr, gl::Graph<SCALAR,DIRECTION> &g, const char* lineArgs = "B")
{
  //using E_MAT = Eigen::SparseMatrix;

  std::vector<Eigen::Triplet<float> > triplets;
  Eigen::Matrix<float, Eigen::Dynamic, 1> degs(g.numNodes());
  //E_MAT adjMat(g.numNodes(), g.numNodes());
  //E_MAT degMat;

  //degMat.setZero();
  //adjMat.setZero();

  // build degree matrix
  for (typename Graph<SCALAR,DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
  {
    //degs(i) = g.getDegree(i);
    triplets.emplace_back(i, i, g.getDegree(i));
  }
  //degMat = degs.asDiagonal();

  std::cout << "Degree matrix built" << std::endl;

  // build adjacency matrix
  for (typename Graph<SCALAR,DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
  {
    typename Graph<SCALAR,DIRECTION>::idx_list_t neighbours = g.getNeighbours(i);
    for (auto n : neighbours)
    {
      //adjMat(i, n) = 1;
      //adjMat(n, i) = 1; // undirected
      triplets.emplace_back(i, n, -1);
      triplets.emplace_back(n, i, -1);
    }
  }

  std::cout << "Adjacency matrix built" << std::endl;

  //E_MAT laplacian = degMat - adjMat;
  Eigen::SparseMatrix<float> laplacian(g.numNodes(), g.numNodes());
  laplacian.setFromTriplets(triplets.begin(), triplets.end());
  laplacian.makeCompressed();

  std::cout << "Laplacian matrix built" << std::endl;

  // calculate eigen vectors
  Eigen::SelfAdjointEigenSolver<Eigen::SparseMatrix<float>> solver;
  solver.compute(laplacian);

  std::cout << "Eigenvectors computed" << std::endl;

  Eigen::MatrixXd positions(2, g.numNodes());

  for (typename Graph<SCALAR,DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
  {
    Eigen::Vector2d pos;
    auto current = solver.eigenvectors();
    pos << current(0, i), current(1, i);

    // Scale by degree
    pos.normalize();
    pos *= 15;
    pos /= (1 + g.getDegree(i)); // Todo: nodes with high degree are now outside, they should be in the middle

    positions.col(i) = pos;
  }

  std::cout << "Positions calculated" << std::endl;

  // set plot ranges
  gr->SetRange('x', positions.row(0).minCoeff(), positions.row(0).maxCoeff());
  gr->SetRange('y', positions.row(1).minCoeff(), positions.row(1).maxCoeff());

  // draw all edges
  for (typename Graph<SCALAR,DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
  {
    typename Graph<SCALAR,DIRECTION>::idx_list_t neighbours = g.getNeighbours(i);
    for (auto n : neighbours)
    {
      mglPoint p1(positions(0, i), positions(1, i));
      mglPoint p2(positions(0, n), positions(1, n));

      gr->Line(p1, p2, lineArgs);
    }
  }
}

} /* namespace external */
} /* namespace gl */

#endif /* GL_WRITE_IMAGE_HPP */