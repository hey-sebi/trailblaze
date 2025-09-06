#ifndef TRAILBLAZE_SPACE_SE2_H_
#define TRAILBLAZE_SPACE_SE2_H_

#include <algorithm>
#include <cmath>

#include "trailblaze/interpolation.h"
#include "trailblaze/traits.h"

namespace trailblaze {

// -------------------- State --------------------
struct SE2 {
  double x;
  double y;
  double yaw;  // radians
};

// -------------------- Accessors --------------------
namespace access {
inline double& x(SE2& s) noexcept { return s.x; }
inline double& y(SE2& s) noexcept { return s.y; }
inline double& yaw(SE2& s) noexcept { return s.yaw; }
inline double x(const SE2& s) noexcept { return s.x; }
inline double y(const SE2& s) noexcept { return s.y; }
inline double yaw(const SE2& s) noexcept { return s.yaw; }
}  // namespace access

// -------------------- Metric(s) --------------------
struct MetricXySe2 {
  template <typename S>
  double operator()(const S& a, const S& b) const {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::hypot(dx, dy);
  }
};

// -------------------- Atomic interpolator(s) --------------------
struct InterpSe2Xy {
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const {
    out.x = LerpScalar::Lerp(a.x, b.x, t);
    out.y = LerpScalar::Lerp(a.y, b.y, t);
  }
};

struct InterpYawShortest {
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const {
    constexpr double kPi = 3.14159265358979323846;
    auto wrap = [](double v) {
      while (v < -kPi) v += 2 * kPi;
      while (v >= kPi) v -= 2 * kPi;
      return v;
    };
    const double a0 = a.yaw;
    double d = wrap(b.yaw - a0);
    out.yaw = wrap(a0 + t * d);
  }
};

// -------------------- Defaults binding --------------------
template <typename S>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<SE2> {
  using Metric = MetricXySe2;
  using Interp = ComposeInterp<InterpSe2Xy, InterpYawShortest>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_SE2_H_
