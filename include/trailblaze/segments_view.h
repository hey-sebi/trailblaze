#ifndef TRAILBLAZE_SEGMENTS_VIEW_H_
#define TRAILBLAZE_SEGMENTS_VIEW_H_

#include <cstddef>
#include <utility>

#include "trailblaze/span.h"

namespace trailblaze {

// Range over consecutive pairs (safe segment iteration).
template <typename S>
class SegmentsView {
 public:
  explicit SegmentsView(Span<S> s) : s_(s) {}

  struct Iterator {
    S* p;
    std::size_t i;
    bool operator!=(const Iterator& o) const { return i != o.i; }
    void operator++() { ++i; }
    std::pair<S&, S&> operator*() const { return {p[i], p[i + 1]}; }
  };

  Iterator begin() const { return {s_.data(), s_.size() >= 2 ? 0u : end().i}; }
  Iterator end() const {
    return {s_.data(),
            s_.size() >= 2 ? static_cast<std::size_t>(s_.size() - 1) : 0u};
  }

 private:
  Span<S> s_;
};

template <typename S>
inline SegmentsView<S> Segments(Span<S> s) {
  return SegmentsView<S>(s);
}

}  // namespace trailblaze

#endif  // TRAILBLAZE_SEGMENTS_VIEW_H_
