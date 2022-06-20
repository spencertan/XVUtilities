#pragma once

#include <type_traits>

/**
 * @brief 
 * * Check specialised template
 */

namespace XV::Traits::Details
{
template <template <typename...> typename Base, typename Derived>
struct Specialised : std::false_type
{};

template <template <typename...> typename Base, typename... Args>
struct Specialised<Base, Base<Args...>> : std::true_type
{};
}


namespace XV::Traits
{
template <template <typename...> typename Base, typename Derived>
inline constexpr bool IsSpecialised()
{
  return Details::Specialised<Base, Derived>::value;
}
}