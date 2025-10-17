/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <algorithm>
#include <cmath>
#include <vector>

#include "trailblaze/interval.h"
#include "trailblaze/path.h"
#include "trailblaze/sampling.h"
#include "trailblaze/state_spaces/state_space_r2.h"
#include "trailblaze/state_spaces/state_space_se2.h"

namespace trailblaze::gen {

/** @brief Generate a straight line in state_r2 between two points.
 *
 */
inline path<state_r2> line_r2(const state_r2& start, const state_r2& goal,
                              sampling::by_count policy) {
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
inline std::vector<state_r2> line_r2(const state_r2& start, const state_r2& direction,
                                     double length, sampling::by_step policy) {
  // note: direction is not necessarily normalized
  const double dir_x = direction.x;
  const double dir_y = direction.y;
  const double magnitude = std::hypot(dir_x, dir_y);
  if (magnitude == 0.0 || length <= 0.0 || policy.step <= 0.0) {
    return {start};
  }

  const double unit_x = dir_x / magnitude;
  const double unit_y = dir_y / magnitude;
  const std::size_t n = static_cast<std::size_t>(std::floor(length / policy.step)) + 1;

  std::vector<state_r2> out;
  out.reserve(n + 1);
  for (std::size_t i = 0; i < n; ++i) {
    double effective_length = std::min(static_cast<double>(i) * policy.step, length);
    out.push_back({start.x + unit_x * effective_length, start.y + unit_y * effective_length});
  }
  // Ensure we hit the final point at the requested length.
  if (out.empty() || std::hypot(out.back().x - (start.x + unit_x * length),
                                out.back().y - (start.y + unit_y * length)) > 1e-12) {
    out.push_back({start.x + unit_x * length, start.y + unit_y * length});
  }
  return out;
}

/**
 *  Generate a set of points along a circular arc in R^2.
 *
 *  Constructs a sequence of 2D points representing a circular arc centered at @p center
 *  with the given @p radius. The arc starts at angle @p start_angle and sweeps through
 *  @p sweep_angle radians. Angles are interpreted in radians, and the arc is sampled
 *  uniformly in the angular domain.
 *
 *  The number of samples is determined by @p sampling_policy. If zero samples are
 *  requested, an empty vector is returned. If exactly one sample is requested, the
 *  function returns the start point only.
 *
 *  @param center The center of the circle in ℝ².
 *  @param radius The circle's radius (must be non-negative).
 *  @param start_angle The starting angle of the arc, in radians.
 *  @param sweep_angle The total angular extent of the arc, in radians. Positive values
 *                     sweep counterclockwise, negative values clockwise.
 *  @param sampling_policy Sampling policy determining how many samples to generate.
 *
 *  @return A vector of 2D states along the arc, evenly spaced by angle.
 *
 *  @note The function does not normalize or constrain angles; @p start_angle and
 *        @p sweep_angle can take arbitrary real values. The returned points
 *        always include the start and end of the arc when @c n ≥ 2.
 */
inline std::vector<state_r2> generate_circle_arc_r2(const state_r2& center,
                                                    double radius,      // NOLINT
                                                    double start_angle, // NOLINT
                                                    double sweep_angle, // NOLINT
                                                    sampling::by_count sampling_policy) {
  std::vector<state_r2> samples;

  const std::size_t sample_count = sampling_policy.n;
  if (sample_count == 0) {
    return samples;
  }

  samples.resize(sample_count);

  for (std::size_t i = 0; i < sample_count; ++i) {
    // Normalized position in [0, 1] across the sample range.
    const double normalized_position =
        (sample_count == 1) ? 0.0 : static_cast<double>(i) / static_cast<double>(sample_count - 1);

    // Compute current angle along the arc.
    const double angle = start_angle + normalized_position * sweep_angle;

    // Compute Cartesian coordinates on the circle.
    samples[i].x = center.x + radius * std::cos(angle);
    samples[i].y = center.y + radius * std::sin(angle);
  }

  return samples;
}

/**
 * Sample a parametric curve P : [t_begin, t_end] → state_r2 at evenly spaced parameters.
 *
 * This function generates a path in R^2 by evaluating a parametric curve at a specified
 * number of evenly spaced parameter values in [t_begin, t_end].
 *
 * If the sampling policy requests zero samples, an empty vector is returned. If exactly
 * one sample is requested, the curve is evaluated at @p t_begin.
 *
 * @tparam Curve A callable type invocable as <tt>state_r2(double)</tt>.
 * @param curve The parametric curve to sample; called as <tt>curve(t)</tt>.
 * @param t_interval The interval [t_begin, t_end], where t_begin is the start and t_end
 *        is the end of the parameter interval.
 * @param sampling_policy Sampling policy indicating the number of samples to take
 *
 * @returns A vector of sampled states.
 *
 * @note This function performs no validation on the ordering of @p t_begin and @p t_end.
 *       If @p t_begin > @p t_end, sampling proceeds in decreasing parameter direction.
 */
template <typename Curve>
inline std::vector<state_r2>
sample_parametric_curve_r2(const Curve& curve, const interval<double>& t_interval, double t_end,
                           sampling::by_count sampling_policy) {
  std::vector<state_r2> samples;

  const std::size_t sample_count = sampling_policy.n;
  if (sample_count == 0) {
    return samples;
  }

  samples.resize(sample_count);

  for (std::size_t i = 0; i < sample_count; ++i) {
    // Normalized position in [0, 1] across the index range [0, sample_count-1].
    const double normalized_position =
        (sample_count == 1) ? 0.0 : static_cast<double>(i) / static_cast<double>(sample_count - 1);

    // Linear interpolation of t between t_begin and t_end.
    const double parameter_t = (1.0 - normalized_position) * t_interval.lower_bound +
                               normalized_position * t_interval.upper_bound;

    samples[i] = curve(parameter_t);
  }

  return samples;
}

} // namespace trailblaze::gen
