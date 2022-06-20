#pragma once

#include "Hash/XXH3.h"
#include <random>
#include <chrono>

namespace XV::Details
{
  struct UID
  {
    i64 time;
    u64 rand;
  };

  inline auto Generate() noexcept
  {
    static std::mt19937_64 gen64;

    return Hash::XXH3_64(UID{
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        gen64()});
  }
}

namespace XV
{
  template <typename Tag = void>
struct GUID
{
  constexpr GUID() noexcept = default;
  constexpr GUID( std::string_view string ) noexcept : value( Hash::XXH3_64( string ) )
  {}
  constexpr GUID( const GUID & ) noexcept = default;
  constexpr GUID( unsigned long long value ) : value( value )
  {}

  constexpr auto operator<=>( const GUID & ) const = default;
  constexpr void SetFromString( std::string_view string ) noexcept
  {
    value = Hash::XXH3_64( string );
  }
  constexpr void Reset() noexcept
  {
    if ( std::is_constant_evaluated() ) SetNull();
    else value = Details::Generate();
  }
  constexpr bool Valid() const noexcept
  {
    return static_cast<bool>( value );
  }
  constexpr void SetNull() noexcept
  {
    value = 0;
  }

  friend std::ostream &operator<<( std::ostream &os, const GUID &guid )
  {
    return os << guid.value;
  }
  u64 value { 0 };
};
}

template <typename Tag>
struct std::hash<typename XV::GUID<Tag>>
{
  auto operator()( const typename XV::GUID<Tag> id ) const
  {
    return id.value;
  }
};