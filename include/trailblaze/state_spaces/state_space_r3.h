#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_R3_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_R3_H_

#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceR3
struct StateR3
{
  double x;
  double y;
  double z;
};

inline std::ostream& operator<<(std::ostream& out, const StateR3& state)
{
  out << "(" << state.x << ", " << state.y << ", " << state.z << ")";
  return out;
}

struct InterpolateR3
{
  void Apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const
  {
    out.x = ScalarInterpolator::Linear(a.x, b.x, t);
    out.y = ScalarInterpolator::Linear(a.y, b.y, t);
    out.z = ScalarInterpolator::Linear(a.z, b.z, t);
  }
};

template <typename TState>
struct StateSpace;  // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<StateR3>
{
  using Metric = EuclideanDistance3D;
  using Interpolation = InterpolationComposition<InterpolateR3>;
};

}  // namespace trailblaze

#endif
