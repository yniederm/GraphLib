#ifndef GL_DISJOINT_SETS_HPP
#define GL_DISJOINT_SETS_HPP

#include <vector>

namespace gl
{
/**
 * The set to which each element belongs to can be found and sets can be merged.
 * @class DisjointSets
 * @brief Represents disjoint sets. 
 */
class DisjointSets {
using idx_t = std::size_t;
public:
  /**
   * @brief Default constructor.
   */
  DisjointSets() = default;
  /**
   * @brief Constructor for fixed number of elements.
   * @param[in] numElems Number of elements in the disjoint sets.
   */
  DisjointSets (idx_t numElems);
  // other constructors
  DisjointSets(const DisjointSets &) = default;                ///< @brief Copy constructor
  DisjointSets(DisjointSets &&) noexcept = default;            ///< @brief Move constructor
  DisjointSets &operator=(const DisjointSets &) = default;     ///< @brief Copy assignment
  DisjointSets &operator=(DisjointSets &&) noexcept = default; ///< @brief Move assignment
  ~DisjointSets() = default;                            ///< @brief Destructor
  /**
   * @brief Finds the set parent of an element.
   * @param[in] elem Element whose set membership is to be found.
   * @return Set parent of given element's set.
   */
  idx_t find (idx_t elem);
  /**
   * @brief Merges two of the disjoint sets.
   * @param[in] one Member of set one.
   * @param[in] two Member of set two.
   */
  void merge (idx_t one, idx_t two);    

private:
  idx_t numElems_;            ///< Initial number of sets.
  std::vector<idx_t> parent_; ///< Parents of every element.
  std::vector<idx_t> rank_;   ///< Ranks of every element in their set.
};

DisjointSets::DisjointSets (idx_t numElems) :
numElems_(numElems), rank_(numElems,0), parent_(numElems) {
  for (idx_t i = 0; i < numElems; ++i) {
    parent_[i] = i;
  }
}

typename DisjointSets::idx_t DisjointSets::find (idx_t elem) {
  if (elem != parent_[elem])
    parent_[elem] = find(parent_[elem]);
  return parent_[elem];
}

void DisjointSets::merge (idx_t one, idx_t two) {
  one = find(one);
  two = find(two); 
  if (rank_[one] > rank_[two]) {
    parent_[two] = one;
  }
  else {
    parent_[one] = two;
  }
  if (rank_[one] == rank_[two])
    ++rank_[two]; 
}

} // namespace gl

#endif // GL_DISJOINT_SETS_HPP