#pragma once

#include <span>

namespace XV
{

  template <typename T,
            std::size_t Extent = std::dynamic_extent>
  using span = std::span<T, Extent>;

}