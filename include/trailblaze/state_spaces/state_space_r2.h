#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_R2_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_R2_H_

#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceR2
struct StateR2
{
  double x;
  double y;
};

inline std::ostream& operator<<(std::ostream& out, const StateR2& state)
{
  out << "(" << state.x << ", " << state.y << ")";
  return out;
}

// ------------ component-wise accessors  -----------------
namespace comp {

inline double& x(StateR2& s) noexcept
{
  return s.x;
}

inline double& y(StateR2& s) noexcept
{
  return s.y;
}

inline double x(const StateR2& s) noexcept
{
  return s.x;
}

inline double y(const StateR2& s) noexcept
{
  return s.y;
}

}  // namespace comp

struct MetricR2
{
  template <typename StateR3>
  double operator()(const StateR3& a, const StateR3& b) const
  {
    // Euclidean distance measure
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::hypot(dx, dy);
  }
};

struct InterpolateR2
{
  template <typename StateR3>
  void Apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const
  {
    out.x = ScalarInterpolator::Linear(a.x, b.x, t);
    out.y = ScalarInterpolator::Linear(a.y, b.y, t);
  }
};

template <typename TState>
struct StateSpace;  // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<StateR2>
{
  using Metric = MetricR2;
  using Interpolation = InterpolationComposition<InterpolateR2>;
};

}  // namespace trailblaze

#endif
