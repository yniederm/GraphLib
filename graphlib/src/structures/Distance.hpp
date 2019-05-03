#ifndef GL_DISTANCE_HPP
#define GL_DISTANCE_HPP

#include <string>

namespace gl 
{
template <class SCALAR>
struct Distance
{

  Distance () : isInfinite_(true), distance_(0) {}     ///< @brief Default constructor
  Distance(const Distance &) = default;                ///< @brief Copy constructor
  Distance(Distance &&) noexcept = default;            ///< @brief Move constructor
  Distance &operator=(const Distance &) = default;     ///< @brief Copy assignment
  Distance &operator=(Distance &&) noexcept = default; ///< @brief Move assignment
  ~Distance() = default;                               ///< @brief Destructor

  /**
   * @brief 'equality' operator
   * @param[in] rhs Distance that will get compared
   * @return true if lhs is equal to rhs, false otherwise
   */
  bool operator == (const Distance& rhs)
  {
    return isInfinite_ == rhs.isInfinite_
        && distance_ == rhs.distance_;
  }
  /**
   * @brief 'inequality' operator
   * @param[in] rhs Distance that will get compared
   * @return true if lhs is not equal to rhs, false otherwise
   */
  bool operator!= (const Distance& rhs)
  {
    return !operator==(rhs);
  }
  /**
   * @brief 'less than' operator
   * @param[in] rhs Distance that will get compared
   * @return true if lhs is less than rhs, false otherwise
   */
  bool operator< (const Distance& rhs)
  {
    if (isInfinite_) return false;
    if (rhs.isInfinite_) return true;
    if (distance_ < rhs.distance_) return true;
    return false;
  }
  /**
   * @brief 'greater than' operator
   * @param[in] rhs Distance that will get compared
   * @return true if lhs is greater than rhs, false otherwise
   */
  bool operator> (const Distance& rhs)
  {
    return !operator<(rhs) && operator!=(rhs);
  }
  /**
   * @brief 'addition' operator
   * @param[in] rhs Distance that will get added to 'this'
   * @return Distance with the combined distances.
   */
  Distance operator+ (const Distance& rhs)
  {
    Distance res; // set to infinite
    if (isInfinite_ || rhs.isInfinite_)
      return res;
    res.setWeight(distance_+rhs.distance_);
    return res;
  }

  /**
   * @brief Gets the distance
   * @return Numerical distance, or 'Inf' if the distance is infinite.
   */
  std::string getWeight() const
  {
    if (isInfinite_) return "Inf";
    return std::to_string(distance_);
  }

  /**
   * @brief Allows updating the distance.
   * @param[in] distance New distance.
   */
  void setWeight (SCALAR distance)
  {
    distance_ = distance;
    isInfinite_ = false;
  }

  /**
   * @brief Checks whether the distance is zero.
   * @return true if the distance is zero, false otherwise
   */
  bool isZero() const
  {
    return !isInfinite_ && distance_ == 0;
  }

  /**
   * @brief Checks whether the distance is infinite.
   * @return true if the distance is infinite, false otherwise
   */
  bool isInfinite() const
  {
    return isInfinite_;
  }

private:
  bool isInfinite_;
  SCALAR distance_;
};

} // namespace gl

#endif // GL_DISTANCE_HPP