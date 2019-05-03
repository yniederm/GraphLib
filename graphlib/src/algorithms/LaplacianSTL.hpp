#ifndef GL_LAPLACIAN_STL_HPP
#define GL_LAPLACIAN_STL_HPP

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

/**
 * @brief Compute the Laplacian Matrix of a graph in an STL vector
 * @param g Graph whose Laplacian will be computed
 * @return Laplacian Matrix in STL vector format
 */
template <class Graph>
std::vector<float> laplacianSTL(const Graph& g)
{
    using matrix_t = std::vector<float>;
    auto numNodes = g.numNodes();
    matrix_t matrix (numNodes*numNodes,0);

    // build degree matrix
    for (typename Graph::idx_t i = 0; i < numNodes; i++)
    {
        matrix[i*numNodes+i] = g.getNodeDegree(i);
    }

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        matrix[it->source()*numNodes+it->dest()] -= 1;
        matrix[it->dest()*numNodes+it->source()] -= 1;
    }

    return matrix;
}

} // namespace algorithm
} // namespace gl

#endif // GL_LAPLACIAN_STL_HPP