/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

/** @file span.h
 *  @brief This file provides a backport of std::span which is only available on C++20 and
 *         later.
 */

#include <cstddef>
#include <type_traits>

#if defined(__has_include)
#if __has_include(<span>) && __cplusplus >= 202002L
#include <span>
#define TRAILBLAZE_HAS_STD_SPAN 1
#endif
#endif

namespace trailblaze {

#if TRAILBLAZE_HAS_STD_SPAN

template <typename T>
using span = std::span<T>;

#else // C++17 substitute

/** Minimal substitute for @see std::span.
 *
 *  Naming/semantics are inteded to be identical to the std implementation.
 *
 *  @note This backport implementation does not have all features of the original class.
 */
template <typename T>
class span {
public:
  using element_type = T;
  using size_type = std::size_t;
  using pointer = T*;
  using reference = T&;
  using iterator = T*;

  constexpr span() noexcept : ptr_(nullptr), len_(0) {}

  constexpr span(pointer data, size_type n) noexcept : ptr_(data), len_(n) {}

  template <typename C, typename = decltype(std::declval<C&>().data()),
            typename = decltype(std::declval<C&>().size())>
  explicit constexpr span(C& container) noexcept
      : ptr_(container.data()), len_(static_cast<size_type>(container.size())) {}

  template <typename C, typename = decltype(std::declval<const C&>().data()),
            typename = decltype(std::declval<const C&>().size())>
  explicit constexpr span(const C& container) noexcept
      : ptr_(container.data()), len_(static_cast<size_type>(container.size())) {}

  [[__nodiscard__]] constexpr pointer data() const noexcept {
    return ptr_;
  }

  [[__nodiscard__]] constexpr size_type size() const noexcept {
    return len_;
  }

  [[__nodiscard__]] constexpr bool empty() const noexcept {
    return len_ == 0;
  }

  [[__nodiscard__]] constexpr iterator begin() const noexcept {
    return ptr_;
  }

  [[__nodiscard__]] constexpr iterator end() const noexcept {
    return ptr_ + len_;
  }

  [[__nodiscard__]] constexpr reference operator[](size_type index) const noexcept {
    return ptr_[index];
  }

  [[__nodiscard__]] constexpr reference front() const noexcept {
    return *ptr_;
  }

  [[__nodiscard__]] constexpr reference back() const noexcept {
    return *(ptr_ + (len_ - 1));
  }

  [[__nodiscard__]] constexpr span subspan(size_type offset,
                                           size_type count = size_type(-1)) const noexcept {
    const size_type n = (count == size_type(-1) || offset + count > len_) ? (len_ - offset) : count;
    return span(ptr_ + offset, n);
  }

private:
  /// Pointer to the start of the data block that we are spanning over.
  pointer ptr_;
  /// Amount of data elements that the span covers.
  size_type len_;
};

#endif // TRAILBLAZE_HAS_STD_SPAN

} // namespace trailblaze
