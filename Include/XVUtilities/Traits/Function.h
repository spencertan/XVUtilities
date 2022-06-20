#pragma once

#include "../Types.h"
#include "../STL_C/Tuple.h"
#include <type_traits>

/**
 * @brief
 * Callable Function
 */

namespace XV::Traits::Function::Details
{
  template <typename T>
  struct Callable
  {
    template <auto U>
    struct Check;

    template <typename>
    static std::false_type Test(...);

    template <typename Func>
    static std::true_type Test(Check<&Func::operator()> *);

    static constexpr auto value = std::is_same_v<decltype(Test<T>(nullptr)), std::true_type>;
  };

  template <typename T>
  constexpr auto is_callable = std::conditional_t<std::is_class<T>::value, Callable<T>, std::false_type>::value;
}

namespace XV::Traits::Function
{
  template <typename Func>
  constexpr auto &is_callable = Details::is_callable<Decay<Func>>;
}

namespace XV::Traits::Concepts
{
  template <typename Func>
  concept CallableFunction = Function::is_callable<Decay<Func>>;
}

/**
 * @brief
 * Function Traits
 */

namespace XV::Traits::Function
{

  /**
   * @brief
   * * Function Signature Details
   */

  namespace Details
  {
    template <bool Exception, typename Return, typename... Args>
    struct Signature
    {
      using Type = Return(Args...) noexcept(Exception);
    };

    template <bool Exception, typename Return>
    struct Signature
    {
      using Type = Return() noexcept(Exception);
    };

    template <bool Exception, typename Return, typename... Args>
    using SignatureType = typename Signature<Exception, Return, Args...>::Type;
  }

  /**
   * @brief
   * * Function Parameters Details
   */
  namespace Details
  {
    template <size_t I, size_t N, typename... Args>
    struct Parameters
    {
      using Type = typename std::tuple_element_t<I, tuple<Args...>>;
    };

    template <>
    struct Parameters<0, 0>
    {
      using Type = void;
    };

    template <size_t I, size_t N, typename... Args>
    using ParametersType = typename Details::Parameters<I, N, Args...>::Type;
  }

  /**
   * @brief 
   * * Function Type 
   */

  template <typename Func>
  struct Type;

  template <bool Exception, typename Return, typename... Args>
  struct Decomposition
  {
    using ClassType = void;
    using ReturnType = Return;
    using SignatureType = Details::SignatureType<Exception, Return, Args...>;
    using ArgsTuple = tuple<Args...>;
    static constexpr size_t args_count = sizeof...(Args);

    template <size_t I>
    using ParametersType = Details::ParametersType<I, args_count, Args...>;
  };

  // functions
  template <typename Return, typename... Args>
  struct Type<Return(Args...) noexcept> : Decomposition<true, Return, Args...>
  {
  };
  template <typename Return, typename... Args>
  struct Type<Return(Args...)> : Decomposition<false, Return, Args...>
  {
  };

  // function pointer
  template <typename Return, typename... Args>
  struct Type<Return (*)(Args...)> : Type<Return(Args...)>
  {
  };
  template <typename Return, typename... Args>
  struct Type<Return (*)(Args...) noexcept> : Type<Return(Args...) noexcept>
  {
  };

  // member function pointer
  template <typename Class, typename Return, typename... Args>
  struct Type<Return (Class::*)(Args...) noexcept> : Type<Return(Args...) noexcept>
  {
    using ClassType = Class;
  };
  template <typename Class, typename Return, typename... Args>
  struct Type<Return (Class::*)(Args...)> : Type<Return(Args...)>
  {
    using ClassType = Class;
  };

  // const member function pointer
  template <typename Class, typename Return, typename... Args>
  struct Type<Return (Class::*)(Args...) const noexcept> : Type<Return(Args...) noexcept>
  {
    using ClassType = Class;
  };
  template <typename Class, typename Return, typename... Args>
  struct Type<Return (Class::*)(Args...) const> : Type<Return(Args...)>
  {
    using ClassType = Class;
  };

  // functors
  template <typename Class>
  struct Type : Type<decltype(&Class::operator())>
  {
    using ClassType = Class;
  };
  template <typename Class>
  struct Type<Class &> : Type<Class>
  {
  };
  template <typename Class>
  struct Type<const Class &> : Type<Class>
  {
  };
  template <typename Class>
  struct Type<Class &&> : Type<Class>
  {
  };
  template <typename Class>
  struct Type<const Class &&> : Type<Class>
  {
  };
  template <typename Class>
  struct Type<Class *> : Type<Class>
  {
  };
  template <typename Class>
  struct Type<const Class *> : Type<Class>
  {
  };

}

namespace XV::Traits::Concepts
{
  template <typename Func, typename Return>
  concept IsFunctionReturnType = std::is_same_v<typename Traits::Function::Type<Func>::ReturnType, Return>;
}