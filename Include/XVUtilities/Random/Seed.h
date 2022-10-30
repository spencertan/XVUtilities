#pragma once
#include "../Types.h"
#include "../Hash/XXH3.h"
#include <random>
#include <source_location>

namespace XV::Random::Details
{
  constexpr u64 SeedC(const std::source_location &location)
  {
    return Hash::XXH3_64(std::string(__TIME__) +
                         location.file_name() +
                         location.function_name()) ^
           location.line();
  }

  u64 Seed()
  {
    std::random_device rd = std::random_device();
    return (static_cast<uint64_t>(rd()) << 32) | static_cast<uint64_t>(rd());
  }
}

namespace XV::Random
{
  constexpr u64 Seed(const std::source_location location = std::source_location::current())
  {
    if (std::is_constant_evaluated())
      return Details::SeedC(location);
    else
      return Details::Seed();
  }
}