/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_GENERATE_H_
#define TRAILBLAZE_GENERATE_H_

#include <algorithm>
#include <cmath>
#include <vector>

#include "trailblaze/path.h"
#include "trailblaze/sampling.h"
#include "trailblaze/state_spaces/state_space_r2.h"
#include "trailblaze/state_spaces/state_space_se2.h"

namespace trailblaze {
namespace gen {

/** @brief Generate a straight line in state_r2 between two points.
 *
 */
inline path<state_r2>
line_r2(const state_r2& start, const state_r2& goal, sampling::by_count policy) {
  path<state_r2> out;
  if (policy.n == 0) {
    return out;
  }
  out.resize(policy.n);
  for (std::size_t i = 0; i < policy.n; ++i) {
    double t = (policy.n == 1) ? 0.0 : static_cast<double>(i) / static_cast<double>(policy.n - 1);
    out[i].x = (1.0 - t) * start.x + t * goal.x;
    out[i].y = (1.0 - t) * start.y + t * goal.y;
  }
  return out;
}

/** @brief Generate a straight line in state_r2 from start with direction and approx length.
 *
 */
inline std::vector<state_r2>
line_r2(const state_r2& start, const state_r2& direction, double length, sampling::by_step policy) {
  // note: direction is not necessarily normalized
  const double dx  = direction.x;
  const double dy  = direction.y;
  const double mag = std::hypot(dx, dy);
  if (mag == 0.0 || length <= 0.0 || policy.step <= 0.0) {
    return {start};
  }

  const double      ux = dx / mag;
  const double      uy = dy / mag;
  const std::size_t n  = static_cast<std::size_t>(std::floor(length / policy.step)) + 1;

  std::vector<state_r2> out;
  out.reserve(n + 1);
  for (std::size_t i = 0; i < n; ++i) {
    double s = std::min(static_cast<double>(i) * policy.step, length);
    out.push_back({start.x + ux * s, start.y + uy * s});
  }
  // Ensure we hit the final point at the requested length.
  if (out.empty() || std::hypot(out.back().x - (start.x + ux * length),
                                out.back().y - (start.y + uy * length)) > 1e-12) {
    out.push_back({start.x + ux * length, start.y + uy * length});
  }
  return out;
}

/** @brief Generate states along a circle arc in R2.
 *
 */
inline std::vector<state_r2> circle_arc_r2(const state_r2&    center,
                                           double             radius,
                                           double             theta0, // start angle (rad)
                                           double             sweep,  // signed sweep (rad)
                                           sampling::by_count policy) {
  std::vector<state_r2> out;
  if (policy.n == 0) {
    return out;
  }
  out.resize(policy.n);
  for (std::size_t i = 0; i < policy.n; ++i) {
    double t = (policy.n == 1) ? 0.0 : static_cast<double>(i) / static_cast<double>(policy.n - 1);
    double a = theta0 + t * sweep;
    out[i].x = center.x + radius * std::cos(a);
    out[i].y = center.y + radius * std::sin(a);
  }
  return out;
}

/** @brief Generate a path in R2 from any parametric curve P:[t0,t1] --> state_r2.
 *
 */
template <typename Curve>
inline std::vector<state_r2>
parametric_r2(const Curve& curve, double t0, double t1, sampling::by_count policy) {
  std::vector<state_r2> out;
  if (policy.n == 0) {
    return out;
  }
  out.resize(policy.n);
  for (std::size_t i = 0; i < policy.n; ++i) {
    double u = (policy.n == 1) ? 0.0 : static_cast<double>(i) / (policy.n - 1);
    double t = (1.0 - u) * t0 + u * t1;
    out[i]   = curve(t);
  }
  return out;
}

} // namespace gen
} // namespace trailblaze

#endif