#pragma once

#include <vector>

namespace XV
{
  template <typename T,
            typename Allocator = std::allocator<T>>
  using vector = std::vector<T, Allocator>;
}