#pragma once

#include "../GUID.h"
#include "../Typelist/Typelist.h"
#include "../STL_C/Vector.h"
#include "../Traits/Specialised.h"
#include "../Helper/NonCopyable.h"
#include <string_view>

namespace XV::Event
{
  using ID = GUID<struct EventID>;
}

namespace XV::Event::Type
{
  struct Global final
  {
    ID m_id{};
    std::string_view m_name{};
  };
}

namespace XV::Event
{

  struct Overrides
  {
    static constexpr auto info = Type::Global{};
  };

  template <typename... Args>
  struct Instance : Overrides, NonCopyable
  {
  private:
    struct Delegate final
    {
      using Callback = FuncPtr<void(Ptr<void>, Args &&...) noexcept>;
      Callback m_callback;
      Ptr<void> m_class;
    };

  public:
    Instance() = default;

    template <auto Func, typename Class>
    inline constexpr void Register(Class &c) noexcept
    {
      m_delegates.emplace_back(
          [](Ptr<void> p, Args && ...args) constexpr noexcept {
            std::invoke(Func, std::bit_cast<Class *>(p), std::forward<Args &&>(args)...);
          },
          &c);
    }

    inline constexpr void Notify(Args &&...args) const noexcept
    {
      for (auto &delegate : m_delegates)
        delegate.m_callback(delegate.m_class, std::forward<Args &&>(args)...);
    }

    vector<Delegate> m_delegates;
  };
}

namespace XV::Event::Concepts
{
  template <typename TEvent>
  concept IsEvent =
      Traits::IsSpecialised<Event::Instance, TEvent>() ||
      std::derived_from<TEvent, Event::Overrides> ||
      std::is_base_of_v<Event::Overrides, TEvent>;

  template <typename List>
  concept IsEventList =
      IsTypelist<List> &&
          []<IsEvent... TEvents>(Typelist<TEvents...>) constexpr noexcept
  {
    return true;
  }
  (List());
}