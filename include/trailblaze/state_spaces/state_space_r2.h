/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cmath>
#include <ostream>

#include "trailblaze/interpolation_composition.h"
#include "trailblaze/math/interpolation.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the state space R2
struct state_r2 {
  /// The x coordinate.
  double x{0.};
  /// The y coordinate.
  double y{0.};
};

inline std::ostream& operator<<(std::ostream& out, const state_r2& state) {
  out << "(" << state.x << ", " << state.y << ")";
  return out;
}

struct interpolate_r2 {
  template <typename StateR3>
  static void apply(const StateR3& a, const StateR3& b, double ratio, StateR3& out) {
    out.x = scalar_interpolator::linear(a.x, b.x, ratio);
    out.y = scalar_interpolator::linear(a.y, b.y, ratio);
  }
};

template <typename TState>
struct state_space; // NOLINT(readability/identifier_naming) TODO: remove?

template <>
struct state_space<state_r2> {
  using metric_type = euclidean_distance_2d;
  using interpolation_type = interpolation_composition<interpolate_r2>;
};

} // namespace trailblaze
