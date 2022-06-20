#pragma once
#include "../Types.h"
#include "Specialised.h"
#include "../STL_C/Tuple.h"

namespace XV::Traits::Concepts
{
  template <typename TupleType>
  concept IsTuple = Traits::IsSpecialised<tuple, TupleType>();
}

/*
 * Tuple Sort
 */

// From: https://codereview.stackexchange.com/questions/131194/selection-sorting-a-type-list-compile-time

namespace XV::Traits::Tuple::Details
{
  // swap types at index I and index J in the template argument tuple
  template <size_t I, size_t J>
  class ElementSwap
  {
    template <typename TupleType, typename Indices>
    struct Implementation;

    template <typename TupleType, size_t... Indices>
    struct Implementation<TupleType,std::index_sequence<Indices...>>
    {
      using Type = tuple<
          std::tuple_element_t<Indices != I && Indices != J ? Indices : Indices == I ? J
                                                                                     : I,
                               TupleType>...>;
    };

  public:
    template <typename TupleType>
    using Type = typename Implementation<TupleType, std::make_index_sequence<std::tuple_size<TupleType>::value>>::Type;
  };

  template <template <typename, typename> typename Comparator, typename TupleType>
  class SelectionSort
  {
    template <size_t I, size_t J, size_t TupleSize, typename LoopTupleType>
    struct Implementation
    {
      // selection sort's "loop"
      // this is done until we have compared every element in the type list
      // true: swap(I, J)
      // false: do nothing
      using Loop = typename Comparator<
          std::tuple_element_t<I, LoopTupleType>,
          std::tuple_element_t<J, LoopTupleType>>::template Type<typename ElementSwap<I, J>::template Type<LoopTupleType>,
                                                             LoopTupleType>;

      // recurse until J == TupleSize using the modified tuple
      using Type = typename Implementation<I, J + 1, TupleSize, Loop>::Type;
    };

    template <size_t I, size_t TupleSize, typename LoopTupleType>
    struct Implementation<I, TupleSize, TupleSize, LoopTupleType>
    {
      // once J == TupleSize, we increment I and start J at I + 1 and recurse
      using Type = typename Implementation<I + 1, I + 2, TupleSize, LoopTupleType>::Type;
    };

    template <size_t J, size_t TupleSize, typename LoopTupleType>
    struct Implementation<TupleSize, J, TupleSize, LoopTupleType>
    {
      // once I == TupleSize, we know that every element has been compared
      using Type = LoopTupleType;
    };

  public:
    using Type = typename Implementation<0, 1, std::tuple_size<TupleType>::value, TupleType>::Type;
  };

  /*
   * Tuple Index
   */

  template <typename T, typename Ts>
  struct Index;

  template <typename T, typename... Ts>
  struct Index<T, tuple<T, Ts...>>
  {
    static constexpr size_t value = 0;
  };

  template <typename T, typename U, typename... Ts>
  struct Index<T, tuple<U, Ts...>>
  {
    static constexpr size_t value = 1 + Index<T, tuple<Ts...>>::value;
  };
}

namespace XV::Traits::Tuple
{

  template <Concepts::IsTuple TupleType>
  constexpr auto null = static_cast<Ptr<TupleType>>(nullptr);

  template <typename... Args>
  constexpr auto make_null = static_cast<Ptr<tuple<Args...>>>(nullptr);

  template <Concepts::IsTuple... Tuples>
  using CatType = decltype(tuple_cat(std::declval<Tuples>()...));

  template <Concepts::IsTuple TupleType>
  using Decay = std::invoke_result_t<decltype([]<typename... Ts>(tuple<Ts...> *) -> tuple<Decay<Ts>...>
                                            {}),
                                   TupleType *>;

  template <typename T, Concepts::IsTuple TupleType>
  static constexpr auto Index = Details::Index<T, TupleType>::value;

  template <template <typename, typename> typename Comparator, Concepts::IsTuple TupleType>
  using SortType = typename Details::SelectionSort<Comparator, TupleType>::Type;
}