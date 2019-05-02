#ifndef GL_DISTANCE_HPP
#define GL_DISTANCE_HPP

#include <string>

namespace gl 
{
template <class SCALAR>
struct Distance
{

  Distance () : isInfinite_(true), weight_(0) {}
  ~Distance() = default;                               ///< @brief Destructor

  Distance(const Distance &) = default;                ///< @brief Copy constructor
  Distance(Distance &&) noexcept = default;            ///< @brief Move constructor
  Distance &operator=(const Distance &) = default;     ///< @brief Copy assignment
  Distance &operator=(Distance &&) noexcept = default; ///< @brief Move assignment

  bool operator< (const Distance& rhs)
  {
    if (isInfinite_) return false;
    if (rhs.isInfinite_) return true;
    if (weight_ < rhs.weight_) return true;
    return false;
  }
  bool operator == (const Distance& rhs)
  {
    return isInfinite_ == rhs.isInfinite_
        && weight_ == rhs.weight_;
  }
  bool operator!= (const Distance& rhs)
  {
    return !operator==(rhs);
  }
  bool operator> (const Distance& rhs)
  {
    return !operator<(rhs) && operator!=(rhs);
  }

  Distance operator+ (const Distance& rhs)
  {
    Distance res; // set to infinite
    if (isInfinite_ || rhs.isInfinite_)
      return res;
    res.setWeight(weight_+rhs.weight_);
    return res;
  }

  std::string getWeight() const
  {
    if (isInfinite_) return "Inf";
    return std::to_string(weight_);
  }

  void setWeight (SCALAR weight)
  {
    weight_ = weight;
    isInfinite_ = false;
  }

  bool isZero() const
  {
    return !isInfinite_ && weight_ == 0;
  }

  bool isInfinite() const
  {
    return isInfinite_;
  }

private:
  bool isInfinite_;
  SCALAR weight_;
};

} // namespace gl

#endif // GL_DISTANCE_HPP