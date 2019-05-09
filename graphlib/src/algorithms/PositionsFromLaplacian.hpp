#ifndef GL_POSITIONS_FROM_LAPLACIAN_HPP
#define GL_POSITIONS_FROM_LAPLACIAN_HPP

#include "../structures/Graph.hpp"
#include "LaplacianEigenDense.hpp"
#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace gl {
namespace algorithm {

/**
 * @brief Compute node 2D positions using an Eigensolver
 * @param laplacian (Eigen::MatrixXf compatible) Input Laplacian matrix
 * @return Matrix containing 2D-coordinates of node positions
 */
Eigen::MatrixXf PositionsFromLaplacian(Eigen::MatrixXf& laplacian)
{
  Eigen::EigenSolver<Eigen::MatrixXf> solver;
  solver.compute(laplacian);

  Eigen::MatrixXf positions(2, laplacian.cols());
  for (unsigned int i = 0; i < laplacian.cols(); i++)
  {
    Eigen::Vector2f pos;
    pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

    // Scale by degree
    pos.normalize();
    pos *= (1 + laplacian(i,i));

    positions.col(i) = pos;
  }
  return positions;
}

/**
 * @brief Compute node 2D positions using an Eigensolver
 * @param laplacian (Eigen::SparseMatrix<float> compatible) Input Laplacian matrix
 * @return Matrix containing 2D-coordinates of node positions
 */
Eigen::MatrixXf PositionsFromLaplacian(Eigen::SparseMatrix<float>& laplacian)
{
  Eigen::SelfAdjointEigenSolver<Eigen::SparseMatrix<float>> solver;
  solver.compute(laplacian);

  Eigen::MatrixXf positions(2, laplacian.cols());
  for (unsigned int i = 0; i < laplacian.cols(); i++)
  {
    Eigen::Vector2f pos;
    pos << solver.eigenvectors()(0, i), solver.eigenvectors()(1, i);

    // Scale by degree
    pos.normalize();
    pos *= (1 + laplacian.coeffRef(i,i));

    positions.col(i) = pos;
  }
  return positions;
}

} // namespace algorithm
} // namespace gl

#endif // GL_POSITIONS_FROM_LAPLACIAN_HPP