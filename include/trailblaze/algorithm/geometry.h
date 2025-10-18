/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cmath>

#include "trailblaze/math/numbers.h"
#include "trailblaze/span.h"
#include "trailblaze/state_traits.h"

namespace trailblaze {

/** Computes the length of a path or a path segment.
 *  Considers only X and y components of the state space.
 *
 *  @tparam TState State that has X and y components.
 *
 *  @param path_span Path or path segment for which to compute the length.
 *  @returns the length.
 */
template <typename TState>
double length_xy(span<const TState> path_span) {
  static_assert(state_traits<TState>::has_xy, "length_xy: TState must have components x & y");
  if (path_span.size() < 2) {
    return 0.0;
  }
  double length = 0.0;
  for (std::size_t i = 1; i < path_span.size(); ++i) {
    const double dx = path_span[i].x - path_span[i - 1].x;
    const double dy = path_span[i].y - path_span[i - 1].y;
    length += std::hypot(dx, dy);
  }
  return length;
}

/** Normalizes the yaw values of states.
 *  @tparam TState State type. Must satisfy the predicate @e has_yaw_v.
 *  @param path_span The states to work on.
 */
template <typename Logger, typename TState>
void normalize_yaw(span<TState> path_span) {
  static_assert(state_traits<TState>::has_yaw, "normalize_yaw: S must have member yaw");
  TRAILBLAZE_LOG_DBG(Logger, ("normalize_yaw: N=", path_span.size()));
  using numbers::pi;
  using numbers::two_pi;
  for (auto& state : path_span) {
    double y = state.yaw;
    if (y >= pi || y < -pi) {
      y = std::fmod(y + pi, two_pi);
      if (y < 0) {
        y += pi;
      }
      y -= pi;
      state.yaw = y;
    }
  }
}

} // namespace trailblaze
