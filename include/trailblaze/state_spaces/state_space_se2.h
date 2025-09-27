#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE2_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE2_H_

#include <algorithm>
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceSe2
struct StateSe2
{
  double x;
  double y;
  double yaw;  // radians
};

inline std::ostream& operator<<(std::ostream& out, const StateSe2& state)
{
  out << "(" << state.x << ", " << state.y << " | " << state.yaw << ")";
  return out;
}

// ------------ component-wise accessors  -----------------
namespace comp {

inline double& x(StateSe2& s) noexcept
{
  return s.x;
}

inline double& y(StateSe2& s) noexcept
{
  return s.y;
}

inline double& yaw(StateSe2& s) noexcept
{
  return s.yaw;
}

inline double x(const StateSe2& s) noexcept
{
  return s.x;
}

inline double y(const StateSe2& s) noexcept
{
  return s.y;
}

inline double yaw(const StateSe2& s) noexcept
{
  return s.yaw;
}
}  // namespace comp

struct MetricSe2
{
  double operator()(const StateSe2& a, const StateSe2& b) const
  {
    // TODO same as for R2 for now
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::hypot(dx, dy);
  }
};

struct InterpolatePositionSe2
{
  void Apply(const StateSe2& a, const StateSe2& b, double t, StateSe2& out) const
  {
    out.x = ScalarInterpolator::Linear(a.x, b.x, t);
    out.y = ScalarInterpolator::Linear(a.y, b.y, t);
  }
};

struct InterpolateOrientationSe2
{
  template <typename StateR3>
  void Apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const
  {
    out.yaw = InterpolateAngleShortest(a.yaw, b.yaw, t);
  }
};

template <typename TState>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<StateSe2>
{
  using Metric = MetricSe2;
  using Interpolation =
      InterpolationComposition<InterpolatePositionSe2, InterpolateOrientationSe2>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_SE2_H_
