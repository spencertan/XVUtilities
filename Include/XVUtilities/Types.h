#pragma once

#include <cstddef>    // byte, size_t, ptrdiff_t, nullptr_t, max_align_t
#include <cstdint>    // signed/unsigned int 8,16,32,64 and their respective min/max
#include <memory>     // unique_ptr, shared_ptr, weak_ptr
#include <functional> // function

namespace XV
{

  /**
   * @brief
   * * cstddef alias
   */

  using byte = std::byte;
  using size_t = std::size_t;
  using ptrdiff_t = std::ptrdiff_t;
  using nullptr_t = std::nullptr_t;
  using max_align_t = std::max_align_t;

  /**
   * @brief
   * * cstdint alias
   */

  // unsigned
  using u8 = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  inline constexpr u8 u8_min = 0;
  inline constexpr u8 u8_max = UINT8_MAX;
  inline constexpr u16 u16_min = 0;
  inline constexpr u16 u16_max = UINT16_MAX;
  inline constexpr u32 u32_min = 0;
  inline constexpr u32 u32_max = UINT32_MAX;
  inline constexpr u64 u64_min = 0;
  inline constexpr u64 u64_max = UINT64_MAX;

  // signed
  using i8 = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;

  inline constexpr i8 i8_min = INT8_MIN;
  inline constexpr i8 i8_max = INT8_MAX;
  inline constexpr i16 i16_min = INT16_MIN;
  inline constexpr i16 i16_max = INT16_MAX;
  inline constexpr i32 i32_min = INT32_MIN;
  inline constexpr i32 i32_max = INT32_MAX;
  inline constexpr i64 i64_min = INT64_MIN;
  inline constexpr i64 i64_max = INT64_MAX;

  // floating-point
  using f32 = float;
  using f64 = double;

  // pointer
  using uptr_t = std::uintptr_t;
  using iptr_t = std::intptr_t;
  using ptrdiff_t = std::ptrdiff_t;

  template <typename T = void>
  using Ptr = std::add_pointer_t<T>;

  template <typename T>
  using FuncPtr = std::add_pointer_t<T>;

  /**
   * @brief
   * * memory alias
   */

  // unique_ptr
  template <typename T>
  using UniquePtr = std::unique_ptr<T>;

  template <typename T, typename... Args>
  inline UniquePtr<T> MakeUnique(Args &&...args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template <typename T>
  inline UniquePtr<T> MakeUniqueOverwrite(size_t size)
  {
    return std::make_unique_for_overwrite<T>(size);
  }

  // shared_ptr
  template <typename T>
  using SharedPtr = std::shared_ptr<T>;

  template <typename T, typename... Args>
  inline SharedPtr<T> MakeShared(Args &&...args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  // weak_ptr
  template <typename T>
  using WeakPtr = std::weak_ptr<T>;

  /**
   * @brief
   * * functional
   */

  template <typename... Args>
  using Action = std::function<void(Args...)>;

  template <typename T>
  using Func = std::function<T>;

  /**
   * @brief
   * * Utility Type
   */

  template <typename T>
  using Decay = std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>;

  using EmptyLambda = decltype([]() {});

}

namespace XV::Concepts
{
  template <typename T>
  concept IsPointer = std::is_pointer_v<T>;

  template <typename T>
  concept IsReference = std::is_reference_v<T>;
}