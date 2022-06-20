#pragma once

#include <forward_list>

namespace XV
{

  template <typename T,
            typename Allocator = std::allocator<T>>
  using forward_list = std::forward_list<T, Allocator>;

}