#ifndef SPECTRAL_PLACING_HPP
#define SPECTRAL_PLACING_HPP

#include "../structures/Graph.hpp"
#include "PositionsFromLaplacian.hpp"
#include "LaplacianSTL.hpp"

namespace gl
{
namespace algorithm
{

/**
 * @brief Compute node 2D positions using spectral placing
 * @param g Graph for which to compute the positions
 */
template <class Graph>
void SpectralPlacing(Graph &g)
{
    // compute graph laplacian matrix
    auto laplacian = gl::algorithm::LaplacianSTL(g);
    // compute x/y positions
    auto pos = gl::algorithm::PositionsFromLaplacian(laplacian);

    for (typename Graph::idx_t i = 0; i < g.numNodes(); ++i)
    {
        g.updateNode(i, std::make_pair(pos.first[i], pos.second[i]));
    }
}

} // namespace algorithm
} // namespace gl

#endif