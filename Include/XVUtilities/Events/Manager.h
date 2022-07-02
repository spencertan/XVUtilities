#pragma once
#include <cassert>
#include "../Containers/PinnedVector.h"
#include "../STL_C/UnorderedMap.h"
#include "Descriptor.h"

namespace XV::Event
{
  struct Manager final : NonCopyable
  {
    template <Concepts::IsEvent TEvent>
    inline void Register() noexcept
    {
      assert(m_events_map.find(info<TEvent>.m_id) == m_events_map.end());
      m_events.push_back({MakeUnique<TEvent>(), &info<TEvent>});
      m_events_map.emplace(info<TEvent>.m_id, m_events.back().first.get());
    }

    template <Concepts::IsEvent TEvent>
    inline TEvent &Get() noexcept
    {
      auto it = m_events_map.find(info<TEvent>.m_id);
      assert(it != m_events_map.end());
      return *std::bit_cast<TEvent *>(it->second);
    }

    ~Manager()
    {
      for (auto& [ptr, desc] : m_events)
        if ( desc->m_destructor )
          desc->m_destructor(std::bit_cast<Ptr<byte>>(ptr.get()));
    }

    unordered_map<ID, Ptr<Overrides>> m_events_map;
    PinnedVector<std::pair<UniquePtr<Overrides>, Ptr<const Event::Descriptor>>> m_events;
  };
}