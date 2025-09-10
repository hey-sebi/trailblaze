#ifndef TRAILBLAZE_SPACE_SE2_H_
#define TRAILBLAZE_SPACE_SE2_H_

#include <algorithm>
#include <cmath>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/traits.h"

namespace trailblaze {

// -------------------- State --------------------
struct SE2
{
  double x;
  double y;
  double yaw;  // radians
};

// -------------------- Accessors --------------------
namespace access {
inline double& x(SE2& s) noexcept
{
  return s.x;
}

inline double& y(SE2& s) noexcept
{
  return s.y;
}

inline double& yaw(SE2& s) noexcept
{
  return s.yaw;
}

inline double x(const SE2& s) noexcept
{
  return s.x;
}

inline double y(const SE2& s) noexcept
{
  return s.y;
}

inline double yaw(const SE2& s) noexcept
{
  return s.yaw;
}
}  // namespace access

// -------------------- Metric(s) --------------------
struct MetricSe2
{
  template <typename S>
  // same as for R2
  double operator()(const S& a, const S& b) const
  {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::hypot(dx, dy);
  }
};

// -------------------- Atomic interpolator(s) --------------------
struct InterpSe2Xy
{
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const
  {
    out.x = LerpScalar::Lerp(a.x, b.x, t);
    out.y = LerpScalar::Lerp(a.y, b.y, t);
  }
};

struct InterpolateYawAngle
{
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const
  {
    static_assert(has_yaw_v<S>, "InterpolateYawAngle needs states with yaw component");
    access::yaw(out) = InterpolateAngleShortest(access::yaw(a), access::yaw(b), t);
  }
};

// -------------------- Defaults binding --------------------
template <typename S>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<SE2>
{
  using Metric = MetricSe2;
  using Interp = InterpolationComposition<InterpSe2Xy, InterpolateYawAngle>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_SE2_H_
