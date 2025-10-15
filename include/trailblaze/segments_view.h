/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstddef>
#include <utility>

#include "trailblaze/backport/span.h"

namespace trailblaze {

// Range over consecutive pairs (safe segment iteration).
template <typename T>
class segments_view {
public:
  explicit segments_view(span<T> s) : s_(s) {}

  struct iterator {
    T* p;
    std::size_t i;

    bool operator!=(const iterator& o) const {
      return i != o.i;
    }

    void operator++() {
      ++i;
    }

    std::pair<T&, T&> operator*() const {
      return {p[i], p[i + 1]};
    }
  };

  iterator begin() const {
    return {s_.data(), s_.size() >= 2 ? 0u : end().i};
  }

  iterator end() const {
    return {s_.data(), s_.size() >= 2 ? static_cast<std::size_t>(s_.size() - 1) : 0u};
  }

private:
  span<T> s_;
};

template <typename T>
inline segments_view<T> segments(span<T> s) {
  return segments_view<T>(s);
}

} // namespace trailblaze
