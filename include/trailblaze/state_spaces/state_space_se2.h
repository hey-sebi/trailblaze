/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <algorithm>
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceSe2
struct state_se2 {
  /// The x coordinate.
  double x{0.};
  /// The y coordinate.
  double y{0.};
  /// The Rotation around z axis in radians.
  double yaw{0.};
};

inline std::ostream& operator<<(std::ostream& out, const state_se2& state) {
  out << "(" << state.x << ", " << state.y << " | " << state.yaw << ")";
  return out;
}

struct interpolate_position_se2 {
  static void apply(const state_se2& a, const state_se2& b, double ratio, state_se2& out) {
    out.x = scalar_interpolator::linear(a.x, b.x, ratio);
    out.y = scalar_interpolator::linear(a.y, b.y, ratio);
  }
};

struct interpolate_orientation_se2 {
  static void apply(const state_se2& a, const state_se2& b, double ratio, state_se2& out) {
    out.yaw = interpolate_angle_shortest(a.yaw, b.yaw, ratio);
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
