#ifndef GL_SPECTRAL_PLACING_SPARSE_HPP
#define GL_SPECTRAL_PLACING_SPARSE_HPP

#include "../structures/Graph.hpp"
#include "LaplacianEigenSparse.hpp"
#include "PositionsFromLaplacian.hpp"

namespace gl {
namespace algorithm {

/**
 * @brief (Undirected Graph only) Compute node 2D positions using spectral placing
 * @param g Graph for which to compute the positions
 */
template <class S,class ST, class DIR, GL_ENABLE_IF_UNDIRECTED_T>
void SpectralPlacingSparse(Graph<S,ST,DIR>& g)
{
  // compute graph laplacian matrix
  auto laplacian = gl::algorithm::LaplacianEigenSparse(g);
  // compute x/y positions
  auto pos = gl::algorithm::PositionsFromLaplacian(laplacian);
  for (typename Graph<S,ST,DIR>::idx_t i = 0; i < g.numNodes(); ++i)
  {
    g.updateNode(i, std::make_pair(pos(0,i), pos(1,i)));
  }
}

} // namespace algorithm
} // namespace gl

#endif // GL_SPECTRAL_PLACING_SPARSE_HPP