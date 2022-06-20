#pragma once

#include <stack>

namespace XV
{

  template <typename T,
            typename Container = std::deque<T>>
  using stack = std::stack<T, Container>;

}