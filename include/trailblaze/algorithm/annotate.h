/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cmath>

#include "trailblaze/math/angle.h"
#include "trailblaze/path.h"
#include "trailblaze/span.h"
#include "trailblaze/state_spaces/state_space_r2.h"
#include "trailblaze/state_spaces/state_space_se2.h"

namespace trailblaze::annotate {

/** Adds yaw angles to a span of state_r2 states using forward chord (next - current). The last yaw
 *  angle is determined using a backward chord.
 *
 *  With this, orientations follow an approximative pseudo-tangent on the path. The
 *  orientations will be more exact for paths that are dense.
 *  @param states The input states for which to annotate yaw angles.
 *  @returns a path of state_se2 states that contain the original position and newly calculated
 *           angle values
 */
inline path<state_se2> yaw_chord(const span<state_r2>& states) {
  path<state_se2> out;
  if (states.empty()) {
    return out;
  }
  out.reserve(states.size());

  const auto yaw_of = [](const state_r2& a, const state_r2& b) {
    return std::atan2(b.y - a.y, b.x - a.x);
  };

  if (states.size() == 1) {
    out.push_back({states[0].x, states[0].y, 0.0});
    return out;
  }

  for (std::size_t i = 0; i < states.size(); ++i) {
    double yaw = 0.0;
    if (i + 1 < states.size()) {
      // forward difference
      yaw = yaw_of(states[i], states[i + 1]);
    } else {
      // backward difference
      yaw = yaw_of(states[i - 1], states[i]);
    }
    out.push_back({states[i].x, states[i].y, normalized(yaw)});
  }
  return out;
}

/** Add yaw using centered finite differences.
 *
 *  @param states The input states for which to annotate yaw angles.
 *  @returns a path of state_se2 states that contain the original position and newly calculated
 *           angle values
 */
inline path<state_se2> yaw_centered_diff(const span<state_r2> states) {
  path<state_se2> out;
  if (states.empty()) {
    return out;
  }
  if (states.size() == 1) {
    out.push_back({states[0].x, states[0].y, 0.0});
    return out;
  }
  out.reserve(states.size());

  const auto yaw_of = [](const state_r2& a, const state_r2& b) {
    return std::atan2(b.y - a.y, b.x - a.x);
  };

  for (std::size_t i = 0; i < states.size(); ++i) {
    double yaw = 0.0;
    if (i == 0) {
      yaw = yaw_of(states[0], states[1]); // forward at start
    } else if (i + 1 == states.size()) {
      yaw = yaw_of(states[i - 1], states[i]); // backward at end
    } else {
      yaw = yaw_of(states[i - 1], states[i + 1]); // centered
    }
    out.push_back({states[i].x, states[i].y, normalized(yaw)});
  }
  return out;
}

/** Calculate yaw angles by linear interpolation between @p start_yaw and @p end_yaw.
 *  @param states The input states for which to annotate yaw angles.
 *  @returns a path of state_se2 states that contain the original position and newly calculated
 *           angle values
 */
inline path<state_se2> yaw_lerp(const span<state_r2>& states, double start_yaw, double end_yaw) {
  path<state_se2> out;
  out.reserve(states.size());
  if (states.empty()) {
    return out;
  }

  // Shortest angular interpolation
  double diff = normalized(end_yaw - start_yaw);
  for (std::size_t i = 0; i < states.size(); ++i) {
    double t = (states.size() == 1)
                   ? 0.0
                   : static_cast<double>(i) / static_cast<double>(states.size() - std::size_t(1));
    double yaw = normalized(start_yaw + (t * diff));
    out.push_back({states[i].x, states[i].y, yaw});
  }
  return out;
}

/** Attach a constant yaw.
 *  @param states The input states for which to annotate yaw angles.
 *  @returns a path of state_se2 states that contain the original position and newly calculated
 *           angle values
 */
inline path<state_se2> yaw_constant(const span<state_r2>& states, double yaw) {
  path<state_se2> out;
  out.reserve(states.size());
  for (const auto& state : states) {
    out.push_back({state.x, state.y, normalized(yaw)});
  }
  return out;
}

} // namespace trailblaze::annotate
