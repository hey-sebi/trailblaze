/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstddef>
#include <limits>
#include <type_traits>

#include "trailblaze/logging.h"
#include "trailblaze/span.h"
#include "trailblaze/state_space.h"

namespace trailblaze {

// State-agnostic resampler: you inject TMetric and TInterpolation policies.
// TMetric:  double operator()(const S& a, const S& b) const;
// TInterpolation:  S operator()(const S& a, const S& b, double t) const;

/**
 *  Resample a path at approximately uniform spatial intervals.
 *
 *  This function generates a resampled version of an input path by walking along each
 *  consecutive pair of states and inserting intermediate samples whenever the accumulated
 *  path length exceeds the specified @p sample_density.
 *
 *  The resampling relies on two user-supplied functors:
 *   - @p metric(a, b): computes the distance between two states.
 *   - @p interpolator(a, b, t): returns an interpolated state between @p a and @p b,
 *     where @p t in [0, 1] represents the normalized distance along the segment.
 *
 *  The function writes resampled states to the output iterator @p out. The input and
 *  output sequences always include both the first and last states.
 *
 *  Logging (via @p TLogger) can be used for debugging or performance tracing.
 *
 *  @tparam TLogger Logging backend type used with TRAILBLAZE_LOG_DBG.
 *  @tparam TState State type representing an element of the path.
 *  @tparam TMetric Callable type with signature
 *          <tt>double(const TState&, const TState&)</tt>.
 *  @tparam TInterpolation Callable type with signature
 *          <tt>TState(const TState&, const TState&, double t)</tt>.
 *  @tparam OutIt Output iterator type to which resampled states are written.
 *
 *  @param path_span Span over the input path to resample. Must contain at least one
 *         element.
 *  @param sample_density Desired distance between consecutive resampled points. If <= 0,
 *         only the start and end points are written.
 *  @param out Output iterator receiving the resampled sequence.
 *  @param metric wDistance metric functor used to compute segment lengths.
 *  @param interpolator Interpolation functor used to generate intermediate states.
 *
 *  @return The total number of output states written through @p out.
 *
 *  @note The algorithm ensures spacing <= @p sample_density between samples, but small
 *        deviations may occur due to floating-point accumulation.
 *
 *  @warning If @p metric returns zero for consecutive distinct states, no intermediate
 *           samples will be produced for that segment.
 */
template <typename TLogger, typename TState, typename TMetric, typename TInterpolation,
          typename OutIt>
std::size_t resample(span<const TState> path_span, double sample_density, OutIt out, TMetric metric,
                     TInterpolation interpolator) {
  if (path_span.empty()) {
    return 0;
  }

  if (path_span.size() == 1) {
    *out++ = path_span[0];
    return 1;
  }

  if (sample_density <= 0.0) {
    TRAILBLAZE_LOG_DBG(TLogger, ("resample: nonpositive sample_density"));
    *out++ = path_span.front();
    *out++ = path_span.back();
    return 2;
  }

  *out++ = path_span.front();
  std::size_t written_count = 1;

  double carried_distance = 0.0;

  for (std::size_t i = 1; i < path_span.size(); ++i) {
    const TState& previous = path_span[i - 1];
    const TState& current = path_span[i];

    const double segment_length = metric(previous, current);
    if (segment_length <= std::numeric_limits<double>::epsilon()) {
      continue;
    }

    double remaining_length = segment_length;
    while (carried_distance + remaining_length >= sample_density) {
      // Normalized interpolation parameter t in [0, 1] along the segment.
      const double t_along_segment =
          1.0 - (remaining_length - (sample_density - carried_distance)) / segment_length;

      TState interpolated_state = interpolator(previous, current, t_along_segment);
      *out++ = std::move(interpolated_state);
      ++written_count;

      remaining_length -= (sample_density - carried_distance);
      carried_distance = 0.0;
    }

    carried_distance += remaining_length;
  }

  *out++ = path_span.back();
  ++written_count;

  TRAILBLAZE_LOG_DBG(TLogger, ("resample: in=", path_span.size(), " out=", written_count,
                               " sample_density=", sample_density));

  return written_count;
}

/**
 *  Resample a path using the default metric and interpolation from its state space.
 *
 *  Uses `state_space<TState>::metric_type` and `state_space<TState>::interpolation_type`
 *  to compute segment lengths and interpolate between states, respectively. See the
 *  primary overload for algorithm details and guarantees.
 *
 *  @tparam TLogger Logger backend used by the primary overload.
 *  @tparam TState State element type of the path.
 *  @tparam OutIt Output iterator receiving resampled states.
 *
 *  @param path_span Span over the input path to resample (const view).
 *  @param sample_density Desired spacing between consecutive samples; if <= 0, only the
 *         first and last elements are emitted.
 *  @param out Output iterator to which resampled states are written.
 *
 *  @returns The Number of states written to @p out.
 */
template <typename TLogger, typename TState, typename OutIt>
std::size_t resample(span<const TState> path_span, double sample_density, OutIt out) {
  using metric = typename state_space<TState>::metric_type;
  using iterpolation = typename state_space<TState>::interpolation_type;
  return resample<TLogger>(path_span, sample_density, out, metric{}, iterpolation{});
}

// forwarding overload to help template deduction when caller has span<TState>.
template <typename TLogger, typename TState, typename TMetric, typename TInterpolation,
          typename OutIt>
std::size_t resample(span<TState> path_span, double sample_density, OutIt out, TMetric metric,
                     TInterpolation interpolator) {
  using mut_state = std::remove_const_t<TState>;
  return resample<TLogger>(
      span<const mut_state>(static_cast<const mut_state*>(path_span.data()), path_span.size()),
      sample_density, out, metric, interpolator);
}

// forwarding overload using state_space Metric and Interpolation
template <typename TLogger, typename TState, typename OutIt>
std::size_t resample(span<TState> path_span, double sample_density, OutIt out) {
  using mut_state = std::remove_const_t<TState>;
  using metric = typename state_space<mut_state>::metric_type;
  using interpolation = typename state_space<mut_state>::interpolation_type;
  return resample<TLogger>(
      span<const mut_state>(static_cast<const mut_state*>(path_span.data()), path_span.size()),
      sample_density, out, metric{}, interpolation{});
}

} // namespace trailblaze
