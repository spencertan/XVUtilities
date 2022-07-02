#pragma once

#include "../Types.h"
#include "../Typename.h"
#include "../GUID.h"
namespace XV::Service
{

  using ID = GUID<struct ServiceID>;

  struct Descriptor
  {
    using Destructor = FuncPtr<void(Ptr<byte>) noexcept>;

    Destructor destructor{nullptr};
    ID id{};
    std::string_view name{};
  };

  namespace Details
  {

    template <typename TService>
    consteval Descriptor CreateDescriptor() noexcept
    {
      Descriptor result_desc;

      // ID
      result_desc.id = ID(__FUNCSIG__);

      // Name
      result_desc.name = Typename<TService>();

      // Destructor
      if constexpr (std::is_trivially_destructible_v<TService>)
        result_desc.destructor = nullptr;
      else
        result_desc.destructor = [](Ptr<byte> p) noexcept
        {
          std::destroy_at(std::bit_cast<Ptr<TService>>(p));
        };
      return result_desc;
    }

    template <typename TService>
    inline constexpr auto desc = CreateDescriptor<TService>();
  }

  template <typename TService>
  inline constexpr auto &info = Details::desc<Raw<TService>>;
}