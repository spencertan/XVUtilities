#pragma once

#include "Instance.h"

namespace XV::Event
{
  struct Descriptor final
  {
    using Destructor = FuncPtr<void(Ptr<byte>) noexcept>;
    Destructor destructor;
    ID id;
    std::string_view name;
  };
}

namespace XV::Event::Details
{
  template <Concepts::IsEvent T>
  consteval Descriptor CreateDescriptor() noexcept
  {
    Descriptor descriptor;
    if constexpr (T::info.id.value)
      descriptor.id = T::info.id;
    else
      descriptor.id = ID(__FUNCSIG__);

    if constexpr (std::is_trivially_destructible_v<T>)
      descriptor.destructor = nullptr;
    else
      descriptor.destructor = [](Ptr<byte> p) noexcept
      {
        std::destroy_at(std::bit_cast<Ptr<T>>(p));
      };

    if constexpr (T::info.name.empty())
      descriptor.name = Typename<T>();
    else
      descriptor.name = T::info.name;
    return descriptor;
  }

  template <typename TEvent>
  inline constexpr auto desc = CreateDescriptor<TEvent>();
}

namespace XV::Event
{
  template <typename TEvent>
  static constexpr auto &info = Details::desc<Decay<TEvent>>;
}