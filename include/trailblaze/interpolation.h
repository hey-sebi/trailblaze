#ifndef TRAILBLAZE_INTERPOLATION_H_
#define TRAILBLAZE_INTERPOLATION_H_

#include <cmath>

namespace trailblaze {

// Simple scalar lerp helper.
struct LerpScalar {
  template <typename T>
  static T Lerp(const T& a, const T& b, double t) {
    return a + (b - a) * t;
  }
};

// Compose multiple atomic interpolator pieces; each piece provides:
//   void Apply(const S& a, const S& b, double t, S& out) const;
template <typename... Pieces>
struct ComposeInterp {
  template <typename S>
  S operator()(const S& a, const S& b, double t) const {
    S out = b;  // copy target layout, then overwrite touched components
    (Pieces{}.Apply(a, b, t, out), ...);
    return out;
  }
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_INTERPOLATION_H_
