/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_R2_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_R2_H_

#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceR2
struct StateR2 {
  double x;
  double y;
};

inline std::ostream& operator<<(std::ostream& out, const StateR2& state) {
  out << "(" << state.x << ", " << state.y << ")";
  return out;
}

struct InterpolateR2 {
  template <typename StateR3>
  void Apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const {
    out.x = ScalarInterpolator::Linear(a.x, b.x, t);
    out.y = ScalarInterpolator::Linear(a.y, b.y, t);
  }
};

template <typename TState>
struct StateSpace; // NOLINT(readability/identifier_naming)

template <>
struct StateSpace<StateR2> {
  using Metric        = EuclideanDistance2D;
  using Interpolation = InterpolationComposition<InterpolateR2>;
};

} // namespace trailblaze

#endif
