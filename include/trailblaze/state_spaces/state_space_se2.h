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
struct state_se2 {
  double x;
  double y;
  double yaw; // radians
};

inline std::ostream& operator<<(std::ostream& out, const state_se2& state) {
  out << "(" << state.x << ", " << state.y << " | " << state.yaw << ")";
  return out;
}

struct interpolate_position_se2 {
  void apply(const state_se2& a, const state_se2& b, double t, state_se2& out) const {
    out.x = scalar_interpolator::linear(a.x, b.x, t);
    out.y = scalar_interpolator::linear(a.y, b.y, t);
  }
};

struct interpolate_orientation_se2 {
  void apply(const state_se2& a, const state_se2& b, double t, state_se2& out) const {
    out.yaw = interpolate_angle_shortest(a.yaw, b.yaw, t);
  }
};

template <typename TState>
struct state_space; // NOLINT // TODO: remove?

template <>
struct state_space<state_se2> {
  using metric_type = euclidean_distance_2d; // TODO: only considers translation for now
  using interpolation_type =
      interpolation_composition<interpolate_position_se2, interpolate_orientation_se2>;
};

} // namespace trailblaze

#endif
