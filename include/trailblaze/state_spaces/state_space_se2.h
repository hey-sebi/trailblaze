/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE2_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE2_H_

#include <algorithm>
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceSe2
struct StateSe2 {
  double x;
  double y;
  double yaw; // radians
};

inline std::ostream& operator<<(std::ostream& out, const StateSe2& state) {
  out << "(" << state.x << ", " << state.y << " | " << state.yaw << ")";
  return out;
}

struct InterpolatePositionSe2 {
  void Apply(const StateSe2& a, const StateSe2& b, double t, StateSe2& out) const {
    out.x = ScalarInterpolator::Linear(a.x, b.x, t);
    out.y = ScalarInterpolator::Linear(a.y, b.y, t);
  }
};

struct InterpolateOrientationSe2 {
  template <typename StateR3>
  void Apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const {
    out.yaw = InterpolateAngleShortest(a.yaw, b.yaw, t);
  }
};

template <typename TState>
struct StateSpace; // NOLINT

template <>
struct StateSpace<StateSe2> {
  using Metric        = EuclideanDistance2D; // TODO: only considers translation for now
  using Interpolation = InterpolationComposition<InterpolatePositionSe2, InterpolateOrientationSe2>;
};

} // namespace trailblaze

#endif
