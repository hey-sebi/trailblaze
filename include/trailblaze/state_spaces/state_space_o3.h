#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_O3_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_O3_H_

#include <algorithm>
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/quaternion_distance.h"

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
  using Metric = QuaternionDistance;
  using Interpolation = InterpolationComposition<InterpolateO3>;
};

}  // namespace trailblaze

#endif
