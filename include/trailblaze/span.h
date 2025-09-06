#ifndef TRAILBLAZE_SPAN_H_
#define TRAILBLAZE_SPAN_H_

#include <cstddef>
#include <type_traits>

#if defined(__has_include)
#if __has_include(<span>) && __cplusplus >= 202002L
#include <span>
#define TRAILBLAZE_HAS_STD_SPAN 1
#endif
#endif

namespace trailblaze {

#if PATH_HAS_STD_SPAN

template <typename T>
using Span = std::span<T>;

#else  // Minimal C++17 substitute

template <typename T>
class Span {
 public:
  using element_type = T;
  using size_type = std::size_t;
  using pointer = T*;
  using reference = T&;
  using iterator = T*;

  constexpr Span() noexcept : ptr_(nullptr), len_(0) {}
  constexpr Span(pointer p, size_type n) noexcept : ptr_(p), len_(n) {}

  template <typename C,
            typename = decltype(std::declval<C&>().data()),
            typename = decltype(std::declval<C&>().size())>
  explicit constexpr Span(C& c) noexcept
      : ptr_(c.data()), len_(static_cast<size_type>(c.size())) {}

  template <typename C,
            typename = decltype(std::declval<const C&>().data()),
            typename = decltype(std::declval<const C&>().size())>
  explicit constexpr Span(const C& c) noexcept
      : ptr_(c.data()), len_(static_cast<size_type>(c.size())) {}

  constexpr pointer data() const noexcept { return ptr_; }
  constexpr size_type size() const noexcept { return len_; }
  constexpr bool empty() const noexcept { return len_ == 0; }

  constexpr iterator begin() const noexcept { return ptr_; }
  constexpr iterator end() const noexcept { return ptr_ + len_; }

  constexpr reference operator[](size_type i) const noexcept { return ptr_[i]; }
  constexpr reference front() const noexcept { return *ptr_; }
  constexpr reference back() const noexcept { return *(ptr_ + (len_ - 1)); }

  constexpr Span subspan(size_type offset,
                         size_type count = size_type(-1)) const noexcept {
    const size_type n =
        (count == size_type(-1) || offset + count > len_) ? (len_ - offset)
                                                          : count;
    return Span(ptr_ + offset, n);
  }

 private:
  pointer ptr_;
  size_type len_;
};

#endif  // TRAILBLAZE_HAS_STD_SPAN

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPAN_H_
