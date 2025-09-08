#ifndef TRAILBLAZE_SPACE_R3_H_
#define TRAILBLAZE_SPACE_R3_H_

#include <cmath>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"

namespace trailblaze {

// -------------------- State --------------------
struct R3
{
  double x;
  double y;
  double z;
};

// -------------------- Accessors --------------------
namespace access {
inline double& x(R3& s) noexcept
{
  return s.x;
}

inline double& y(R3& s) noexcept
{
  return s.y;
}

inline double& z(R3& s) noexcept
{
  return s.z;
}

inline double x(const R3& s) noexcept
{
  return s.x;
}

inline double y(const R3& s) noexcept
{
  return s.y;
}

inline double z(const R3& s) noexcept
{
  return s.z;
}
}  // namespace access

// -------------------- Metric(s) --------------------
struct MetricR3
{
  template <typename S>
  double operator()(const S& a, const S& b) const
  {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    const double dz = a.z - b.z;
    return std::hypot(dx, dy, dz);
  }
};

// -------------------- Atomic interpolator(s) --------------------
struct InterpR3
{
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const
  {
    out.x = LerpScalar::Lerp(a.x, b.x, t);
    out.y = LerpScalar::Lerp(a.y, b.y, t);
    out.z = LerpScalar::Lerp(a.z, b.z, t);
  }
};

// -------------------- Defaults binding --------------------
template <typename S>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<R3>
{
  using Metric = MetricR3;
  using Interp = InterpolationComposition<InterpR3>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_R3_H_
