#ifndef GL_LAPLACIAN_EIGEN_DENSE_HPP
#define GL_LAPLACIAN_EIGEN_DENSE_HPP

#include "../structures/Graph.hpp"
#include <Eigen/Dense>

namespace gl {
namespace algorithm {

/**
 * @brief Compute the Laplacian Matrix of a graph in Eigen::Matrix format
 * @param g Graph whose Laplacian will be computed
 * @return Laplacian Matrix in Eigen Matrix format
 */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class S, class STORAGE, class DIR, GL_ENABLE_IF_DIRECTED_T>
#endif
#ifdef DOXYGEN_SHOULD_SKIP_THIS
template <class class SCALAR, class STORAGE_KIND, class DIRECTION>
#endif
Eigen::MatrixXf LaplacianEigenDense(const Graph<S,STORAGE,DIR>& g)
{
  auto numNodes = g.numNodes();
  Eigen::MatrixXf mat = Eigen::MatrixXf::Zero(numNodes,numNodes);

  // build degree matrix
  for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
  {
      mat(i,i) = static_cast<float>(g.getNodeOutDegree(i));
  }

  // build adjacency matrix
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    mat(it->source(), it->dest()) -= 1.;
  }

  return mat;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class S, class STORAGE, class DIR, GL_ENABLE_IF_MATRIX_UNDIRECTED_T>
Eigen::MatrixXf LaplacianEigenDense(const Graph<S,STORAGE,DIR>& g)
{
  auto numNodes = g.numNodes();
  Eigen::MatrixXf mat = Eigen::MatrixXf::Zero(numNodes,numNodes);

  // build degree matrix
  for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
  {
      mat(i,i) = static_cast<float>(g.getNodeOutDegree(i));
  }

  // build adjacency matrix
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    mat(it->source(), it->dest()) -= 1.;
    mat(it->dest(), it->source()) -= 1.;
  }

  return mat;
}

template <class S, class STORAGE, class DIR, GL_ENABLE_IF_LIST_UNDIRECTED_T>
Eigen::MatrixXf LaplacianEigenDense(const Graph<S,STORAGE,DIR>& g)
{
  auto numNodes = g.numNodes();
  Eigen::MatrixXf mat = Eigen::MatrixXf::Zero(numNodes,numNodes);

  // build degree matrix
  for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
  {
      mat(i,i) = static_cast<float>(g.getNodeOutDegree(i));
  }

  // build adjacency matrix
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
  {
    mat(it->source(), it->dest()) -= 1.;
  }

  return mat;
}
#endif // DOXYGEN_SHOULD_SKIP_THIS

} // namespace algorithm
} // namespace gl

#endif // GL_LAPLACIAN_EIGEN_DENSE_HPP