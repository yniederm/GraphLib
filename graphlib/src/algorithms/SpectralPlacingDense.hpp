#ifndef GL_SPECTRAL_PLACING_DENSE_HPP
#define GL_SPECTRAL_PLACING_DENSE_HPP

#include "../structures/Graph.hpp"
#include "LaplacianEigenDense.hpp"
#include "PositionsFromLaplacian.hpp"
#include <Eigen/Dense>

namespace gl {
namespace algorithm {

/**
 * @brief Compute node 2D positions using spectral placing
 * @param g Graph for which to compute the positions
 */
template <class Graph>
void SpectralPlacingDense(Graph& g)
{
  // compute graph laplacian matrix
  auto laplacian = gl::algorithm::LaplacianEigenDense(g);
  // compute x/y positions
  auto pos = gl::algorithm::PositionsFromLaplacian(laplacian);

  for (typename Graph::idx_t i = 0; i < g.numNodes(); ++i)
  {
    g.updateNode(i, std::make_pair(pos(0,i), pos(1,i)));
  }
}

} // namespace algorithm
} // namespace gl

#endif // GL_SPECTRAL_PLACING_DENSE_HPP