#ifndef GL_SPECTRAL_PLACING_HPP
#define GL_SPECTRAL_PLACING_HPP

#include "../structures/Graph.hpp"
#include "LaplacianEigen.hpp"
#include <Eigen/Dense>

namespace gl {
namespace algorithm {

/**
 * @brief Compute node 2D positions using spectral placing
 * @param g Graph for which to compute the positions
 */
template <class Graph>
void computeSpectralPlacing(Graph& g)
{
    // compute x/y positions
    auto laplacian = gl::algorithm::laplacianEigen(g);

    // calculate eigenvectors
    Eigen::EigenSolver<decltype(laplacian)> solver;
    solver.compute(laplacian);

    for (typename Graph::idx_t i = 0; i < g.numNodes(); i++)
    {
        Eigen::Vector2f pos;
        pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

        // Scale by degree
        pos.normalize();
        pos *= (1 + g.getNodeDegree(i));
        g.updateNode(i, std::make_pair(pos(0), pos(1)));
    }
}

} // namespace algorithm
} // namespace gl

#endif // GL_SPECTRAL_PLACING_HPP