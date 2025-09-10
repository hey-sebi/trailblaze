#ifndef TRAILBLAZE_SPACE_R2_H_
#define TRAILBLAZE_SPACE_R2_H_

#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/state_traits.h"

namespace trailblaze {

// -------------------- State --------------------
struct R2
{
  double x;
  double y;
};

inline std::ostream& operator<<(std::ostream& out, const R2& state)
{
  out << "(" << state.x << ", " << state.y << ")";
  return out;
}

// -------------------- Accessors --------------------
namespace access {
inline double& x(R2& s) noexcept
{
  return s.x;
}

inline double& y(R2& s) noexcept
{
  return s.y;
}

inline double x(const R2& s) noexcept
{
  return s.x;
}

inline double y(const R2& s) noexcept
{
  return s.y;
}
}  // namespace access

// -------------------- Metric(s) --------------------
struct MetricR2
{
  template <typename S>
  double operator()(const S& a, const S& b) const
  {
    // For R2 it’s trivial, but made generic to accept any S with x,y.
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::hypot(dx, dy);
  }
};

// -------------------- Atomic interpolator(s) --------------------
struct InterpR2
{
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const
  {
    out.x = LerpScalar::Lerp(a.x, b.x, t);
    out.y = LerpScalar::Lerp(a.y, b.y, t);
  }
};

// -------------------- Defaults binding --------------------
// Forward declare primary in state_space.h; specialize here.
template <typename S>
struct StateSpace;  // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<R2>
{
  using Metric = MetricR2;
  using Interp = InterpolationComposition<InterpR2>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_R2_H_
