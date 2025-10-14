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

/// Models a state belonging to the state space R2
struct state_r2 {
  double x;
  double y;
};

inline std::ostream& operator<<(std::ostream& out, const state_r2& state) {
  out << "(" << state.x << ", " << state.y << ")";
  return out;
}

struct interpolate_r2 {
  template <typename StateR3>
  void apply(const StateR3& a, const StateR3& b, double t, StateR3& out) const {
    out.x = scalar_interpolator::linear(a.x, b.x, t);
    out.y = scalar_interpolator::linear(a.y, b.y, t);
  }
};

template <typename TState>
struct state_space; // NOLINT(readability/identifier_naming) TODO: remove?

template <>
struct state_space<state_r2> {
  using metric_type        = euclidean_distance_2d;
  using interpolation_type = interpolation_composition<interpolate_r2>;
};

} // namespace trailblaze

#endif
