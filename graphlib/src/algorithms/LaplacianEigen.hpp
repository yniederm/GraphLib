#ifndef GL_LAPLACIAN_EIGEN_HPP
#define GL_LAPLACIAN_EIGEN_HPP

#include "../structures/Graph.hpp"
#include <Eigen/Dense>

namespace gl {
namespace algorithm {

/**
 * @brief Compute the Laplacian Matrix of a graph in EigenMmatrix format
 * @param g Graph whose Laplacian will be computed
 * @return Laplacian Matrix in Eigen Matrix format
 */
template <class Graph>
Eigen::MatrixXf laplacianEigen(const Graph& g)
{
    auto numNodes = g.numNodes();
    Eigen::MatrixXf mat = Eigen::MatrixXf::Zero(numNodes,numNodes);

    // build degree matrix
    for (typename Graph::idx_t i = 0; i < numNodes; i++)
    {
        mat(i,i) = g.getNodeDegree(i);
    }

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        mat(it->source(), it->dest()) -= 1;
        mat(it->dest(), it->source()) -= 1;
    }

    return mat;
}

} // namespace algorithm
} // namespace gl

#endif // GL_LAPLACIAN_EIGEN_HPP