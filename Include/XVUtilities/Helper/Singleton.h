#pragma once

#include "NonCopyable.h"

namespace XV
{
  template <typename T>
  class Singleton : NonCopyable
  {
  public:
    static T &Instance()
    {
      static T instance;
      return instance;
    }

  protected:
    Singleton() = default;
    ~Singleton() = default;
  };
}