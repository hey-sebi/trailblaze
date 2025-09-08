#ifndef TRAILBLAZE_SPACE_O3_H_
#define TRAILBLAZE_SPACE_O3_H_

#include <algorithm>
#include <cmath>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"

namespace trailblaze {

// -------------------- State --------------------
struct O3
{
  Quaternion orientation;
};

// -------------------- Accessors --------------------
namespace access {
inline double& qx(O3& s) noexcept
{
  return s.orientation.x;
}

inline double& qy(O3& s) noexcept
{
  return s.orientation.y;
}

inline double& qz(O3& s) noexcept
{
  return s.orientation.z;
}

inline double& qw(O3& s) noexcept
{
  return s.orientation.w;
}

inline double qx(const O3& s) noexcept
{
  return s.orientation.x;
}

inline double qy(const O3& s) noexcept
{
  return s.orientation.y;
}

inline double qz(const O3& s) noexcept
{
  return s.orientation.z;
}

inline double qw(const O3& s) noexcept
{
  return s.orientation.w;
}

}  // namespace access

// -------------------- Metric(s) --------------------
struct MetricO3
{
  template <typename S>
  double operator()(const S& a, const S& b) const
  {
    Quaternion diff;
    diff.x = a.x - b.x;
    diff.y = a.x - b.y;
    diff.z = a.x - b.z;
    diff.w = a.x - b.w;
    return Norm(diff);
  }
};
// -------------------- Atomic interpolator(s) --------------------
struct InterpolateQuaternionSlerp
{
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const
  {
    static_assert(kHasQuat<S>, "State must have quaternion orientation");
    out.orientation = InterpolateQuaternion(a.orientation, b.orientation, t);
  }
};


// -------------------- Defaults binding --------------------
// Forward declare primary in state_space.h; specialize here.
template <typename S>
struct StateSpace;  // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<O3>
{
  using Metric = MetricO3;
  using Interp = InterpolationComposition<InterpolateQuaternionSlerp>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_O3_H_
