#ifndef GL_BASE_HPP
#define GL_BASE_HPP

#include <limits>
#include <cstdint>

#define GL_INF(ValueType) \
std::numeric_limits<ValueType>::max()

namespace gl
{
  using index_type = std::size_t;
} // namespace gl

#endif // GL_BASE_HPP