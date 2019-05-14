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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class S, class STORAGE, class DIR, GL_ENABLE_IF_DIRECTED_T>
#endif
#ifdef DOXYGEN_SHOULD_SKIP_THIS
template <class class SCALAR, class STORAGE_KIND, class DIRECTION>
#endif
std::vector<float> LaplacianSTL(const Graph<S,STORAGE,DIR>& g)
{
    using matrix_t = std::vector<float>;
    auto numNodes = g.numNodes();
    matrix_t matrix (numNodes*numNodes,0);

    // build degree matrix
    for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
    {
        matrix[i*numNodes+i] = g.getNodeOutDegree(i);
    }

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        matrix[it->source()*numNodes+it->dest()] -= 1;
    }

    return matrix;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class S, class STORAGE, class DIR, GL_ENABLE_IF_MATRIX_UNDIRECTED_T>
std::vector<float> LaplacianSTL(const Graph<S,STORAGE,DIR>& g)
{
    using matrix_t = std::vector<float>;
    auto numNodes = g.numNodes();
    matrix_t matrix (numNodes*numNodes,0);

    // build degree matrix
    for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
    {
        matrix[i*numNodes+i] = g.getNodeOutDegree(i);
    }

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        matrix[it->source()*numNodes+it->dest()] -= 1;
        matrix[it->dest()*numNodes+it->source()] -= 1;
    }

    return matrix;
}

template <class S, class STORAGE, class DIR, GL_ENABLE_IF_LIST_UNDIRECTED_T>
std::vector<float> LaplacianSTL(const Graph<S,STORAGE,DIR>& g)
{
    using matrix_t = std::vector<float>;
    auto numNodes = g.numNodes();
    matrix_t matrix (numNodes*numNodes,0);

    // build degree matrix
    for (typename Graph<S,STORAGE,DIR>::idx_t i = 0; i < numNodes; i++)
    {
        matrix[i*numNodes+i] = g.getNodeOutDegree(i);
    }

    // build adjacency matrix
    for (auto it = g.edge_cbegin(); it != g.edge_cend(); it++)
    {
        matrix[it->source()*numNodes+it->dest()] -= 1;
    }

    return matrix;
}
#endif // DOXYGEN_SHOULD_SKIP_THIS


} // namespace algorithm
} // namespace gl

#endif // GL_LAPLACIAN_STL_HPP