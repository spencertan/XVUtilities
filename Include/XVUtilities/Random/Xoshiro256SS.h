#pragma once
#include "../Types.h"
#include "../STL_C/Array.h"
#include "Seed.h"
namespace XV::Random
{

  class Xoshiro256SS
  {
  public:
    using state_type = array<u64, 4>;
    using result_type = u64;

  private:
    state_type _state{};

    constexpr u64 SplitMix64(u64 &x)
    {
      u64 z = (x += 0x9E3779B97F4A7C15UL);
      z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9UL;
      z = (z ^ (z >> 27)) * 0x94D049BB133111EBUL;
      return z ^ (z >> 31);
    }

    __forceinline constexpr u64 ROTL(const u64 x, const u32 s)
    {
      return (x << s) | (x >> (64 - s));
    }

    __forceinline constexpr result_type NextU64()
    {
      const u64 result = ROTL(_state[1] * 5, 7) * 9;
      const u64 t = _state[1] << 17;

      _state[2] ^= _state[0];
      _state[3] ^= _state[1];
      _state[1] ^= _state[2];
      _state[0] ^= _state[3];
      _state[2] ^= t;
      _state[3] = ROTL(_state[3], 45);

      return result;
    }

  public:
    [[nodiscard]] constexpr Xoshiro256SS() noexcept : Xoshiro256SS(Seed()) {}
    [[nodiscard]] constexpr Xoshiro256SS(u64 seed) noexcept
    {
      _state[0] = SplitMix64(seed);
      _state[1] = SplitMix64(seed);
      _state[2] = SplitMix64(seed);
      _state[3] = SplitMix64(seed);
    }

    constexpr result_type operator()() noexcept { return NextU64(); }
    [[nodiscard]] constexpr result_type Min() noexcept { return u64_min; }
    [[nodiscard]] constexpr result_type Max() noexcept { return u64_max; }

    constexpr void Jump() noexcept
    {
      constexpr state_type jump = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c};
      u64 s0 = 0, s1 = 0, s2 = 0, s3 = 0;
      for (const u64 &j : jump)
        for (int b = 0; b < 64; ++b)
        {
          if ((j & (1ull << b)) != 0)
          {
            s0 ^= _state[0];
            s1 ^= _state[1];
            s2 ^= _state[2];
            s3 ^= _state[3];
          }
          NextU64();
        }
      _state[0] = s0;
      _state[1] = s1;
      _state[2] = s2;
      _state[3] = s3;
    }

    constexpr void LongJump() noexcept
    {
      constexpr state_type jump = {0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635};
      u64 s0 = 0, s1 = 0, s2 = 0, s3 = 0;
      for (const u64 &j : jump)
        for (int b = 0; b < 64; ++b)
        {
          if ((j & (1ull << b)) != 0)
          {
            s0 ^= _state[0];
            s1 ^= _state[1];
            s2 ^= _state[2];
            s3 ^= _state[3];
          }
          NextU64();
        }
      _state[0] = s0;
      _state[1] = s1;
      _state[2] = s2;
      _state[3] = s3;
    }
  };

}