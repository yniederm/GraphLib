#ifndef GL_POSITIONS_FROM_LAPLACIAN_HPP
#define GL_POSITIONS_FROM_LAPLACIAN_HPP

#include "../structures/Graph.hpp"

namespace gl
{
namespace algorithm
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * @brief Signature of blas function, see LAPACK guide for information about variables
 */
extern "C" void sgeev_(
    const char &, const char &, const int &, float *,
    const int &, float *, float *, float *, const int &,
    float *, const int &, float *, const int &, int *);
#endif
/**
 * @brief Compute Positions from Laplacian using BLAS routine
 * @param laplacian Vector of floats containing the laplacian of the graph
 * @param factor Stretching-factor for positions
 * @return a pair of the first two eigenvectors scaled by degree and factor
 */
std::pair<std::vector<float>, std::vector<float>> PositionsFromLaplacian(std::vector<float> laplacian, double factor = 5.0)
{
  int N = std::sqrt(laplacian.size());
  int NN = N * N;
  float wr[N]; // 
  float wi[N];
  float eigenvectorsL[NN];
  float eigenvectorsR[NN];
  float work[4 * N]; // aquire enough work space, 3*N is needed
  int info; // whether it worked
  float data[NN];
  for (int i = 0; i < NN; i++)
  {
    data[i] = laplacian.data()[i];
  }
  sgeev_('V', 'N', N, data, N, wr, wi, eigenvectorsR, N, eigenvectorsL, N, work, NN, &info);
  GL_ASSERT(info == 0, "BLAS call was not correct, got " + std::to_string(info) + " instead of 0.");
  std::vector<float> ev1(N);
  std::vector<float> ev2(N);

  for (int i = 0; i < N; i++)
  {
    ev1[i] = eigenvectorsR[i * N] * (1 + laplacian[N * i + i]) * factor; // and scale by degree
    ev2[i] = eigenvectorsR[i * N + 1] * (1 + laplacian[N * i + i]) * factor;
  }
  return std::make_pair(ev1, ev2);
}

} // namespace algorithm
} // namespace gl

#endif // GL_POSITIONS_FROM_LAPLACIAN_HPP