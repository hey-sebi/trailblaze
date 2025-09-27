#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_O3_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_O3_H_

#include <algorithm>
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"

namespace trailblaze {

/// Models a state belongign to the StateSpaceO3
struct StateO3
{
  Quaternion orientation;
};

inline std::ostream& operator<<(std::ostream& out, const StateO3& state)
{
  out << "(" << state.orientation.x << ", " << state.orientation.y << ", "
      << state.orientation.z << "| " << state.orientation.w << ")";
  return out;
}

// ------------ component-wise accessors  -----------------
namespace comp {

inline double& qx(StateO3& s) noexcept
{
  return s.orientation.x;
}

inline double& qy(StateO3& s) noexcept
{
  return s.orientation.y;
}

inline double& qz(StateO3& s) noexcept
{
  return s.orientation.z;
}

inline double& qw(StateO3& s) noexcept
{
  return s.orientation.w;
}

inline double qx(const StateO3& s) noexcept
{
  return s.orientation.x;
}

inline double qy(const StateO3& s) noexcept
{
  return s.orientation.y;
}

inline double qz(const StateO3& s) noexcept
{
  return s.orientation.z;
}

inline double qw(const StateO3& s) noexcept
{
  return s.orientation.w;
}

}  // namespace comp

struct MetricO3
{
  double operator()(const StateO3& a, const StateO3& b) const
  {
    Quaternion diff;
    diff.x = a.orientation.x - b.orientation.x;
    diff.y = a.orientation.x - b.orientation.y;
    diff.z = a.orientation.x - b.orientation.z;
    diff.w = a.orientation.x - b.orientation.w;
    return Norm(diff);
  }
};

struct InterpolateO3
{
  void Apply(const StateO3& a, const StateO3& b, double t, StateO3& out) const
  {
    out.orientation = InterpolateQuaternion(a.orientation, b.orientation, t);
  }
};

template <typename TState>
struct StateSpace;  // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<StateO3>
{
  using Metric = MetricO3;
  using Interpolation = InterpolationComposition<InterpolateO3>;
};

}  // namespace trailblaze

#endif
