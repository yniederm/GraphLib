#ifndef GL_HAVEL_HAKIMI_HPP
#define GL_HAVEL_HAKIMI_HPP

#include <string>
#include <queue>
#include <numeric>

namespace gl {
namespace algorithm {

/**
 * @brief Uses the Havel-Hakimi algorithm to determine whether a given degree sequence is graphic.
 * @param[in] degrees Deque representation of a degree sequence
 * @return True if sequence is graphic, false otherwise.
 */
bool havelHakimi (std::deque<gl::index_type> degrees)
{
  using idx_t = gl::index_type;
  std::sort(degrees.begin(), degrees.end(), [](idx_t a, idx_t b){
    return a > b;
  });

  // check if any entries are negative (only last element needs to be checked, because sorted)
  if (degrees.back() < 0) return false;
  // check if any degrees exceed number of nodes-1 (only first element needs to be checked, because sorted)
  if (degrees.front() > degrees.size() - 1) return false;
  // sum of degrees must be even
  if (std::accumulate(degrees.begin(),degrees.end(), 0) % 2) return false;
  // check if all elements are zero (only front element needs to be checked because sorted)
  if (!degrees.front()) return true;

  auto degree = degrees.front();
  degrees.pop_front();

  for (idx_t i = 0; i < degree; ++i) {
    --degrees[i];
  }

  return havelHakimi(std::move(degrees));
}

/**
 * @brief Uses the Havel-Hakimi algorithm to determine whether a given degree sequence is graphic.
 * @param[in] degreeSeq String representation of a degree sequence: e.g. "3 3 2 1 1 0"
 * @return True if sequence is graphic, false otherwise.
 */
bool isGraphicSequence (const std::string& degreeSeq) 
{
  using idx_t = gl::index_type;
  std::stringstream iss(degreeSeq);
  idx_t degree;
  std::deque<idx_t> degrees;
  while( iss >> degree )
    degrees.push_back(degree);
    
  return gl::algorithm::havelHakimi(std::move(degrees));
}

} // namespace algorithm  
} // namespace gl  

#endif // GL_HAVEL_HAKIMI_HPP