#ifndef SPECTRAL_PLACING_HPP
#define SPECTRAL_PLACING_HPP

#include "../structures/Graph.hpp"
#include <Eigen/Dense>

namespace gl
{
namespace algorithm
{

/**
 * @brief Compute positions using spectral placing
 * @param g Graph for which to compute the positions
 */
template <class SCALAR, class STORAGE_KIND, class DIRECTION>
void computeSpectralPlacing(gl::Graph<SCALAR, STORAGE_KIND, DIRECTION> &g)
{
    // calculate x,y positions
    using E_MAT = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
    Eigen::Matrix<float, Eigen::Dynamic, 1> degs(g.numNodes());
    E_MAT adjMat(g.numNodes(), g.numNodes());
    E_MAT degMat;

    degMat.setZero();
    adjMat.setZero();

    // build degree matrix
    for (typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
    {
        degs(i) = g.getNodeDegree(i);
    }
    degMat = degs.asDiagonal();

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        adjMat(it->source(), it->dest()) = 1;
        adjMat(it->dest(), it->source()) = 1;
    }

    E_MAT laplacian = degMat - adjMat;

    // calculate eigen vectors
    Eigen::EigenSolver<E_MAT> solver;
    solver.compute(laplacian);

    for (typename Graph<SCALAR, STORAGE_KIND, DIRECTION>::idx_t i = 0; i < g.numNodes(); i++)
    {
        Eigen::Vector2f pos;
        pos << solver.eigenvectors()(0, i).real(), solver.eigenvectors()(1, i).real();

        // Scale by degree
        pos.normalize();
        pos *= (1 + g.getNodeDegree(i));
        g.updateNode(i, std::make_pair(pos(0), pos(1)));
    }
}

} /* namespace algorithm */

} /* namespace gl */

#endif /* SPECTRAL_PLACING_HPP */