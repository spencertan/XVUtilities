#pragma once

#include <deque>

namespace XV
{

  template <typename T,
            typename Allocator = std::allocator<T>>
  using deque = std::deque<T, Allocator>;

}