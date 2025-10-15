/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstddef>
#include <limits>
#include <type_traits>

#include "trailblaze/backport/span.h"
#include "trailblaze/logging.h"
#include "trailblaze/state_space.h"

namespace trailblaze {

// State-agnostic resampler: you inject TMetric and TInterpolation policies.
// TMetric:  double operator()(const S& a, const S& b) const;
// TInterpolation:  S operator()(const S& a, const S& b, double t) const;
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
  if (sample_density <= 0) {
    TRAILBLAZE_LOG_DBG(TLogger, ("resample: nonpositive sample_density"));
    *out++ = path_span.front();
    *out++ = path_span.back();
    return 2;
  }

  *out++ = path_span.front();
  std::size_t written = 1;

  double carry = 0.0;
  for (std::size_t i = 1; i < path_span.size(); ++i) {
    const TState& a = path_span[i - 1];
    const TState& b = path_span[i];

    const double seg = metric(a, b);
    if (seg <= std::numeric_limits<double>::epsilon()) {
      continue;
    }

    double remaining = seg;
    while (carry + remaining >= sample_density) {
      // absolute t in [0,1] along the current segment
      const double t_abs = 1.0 - (remaining - (sample_density - carry)) / seg;
      TState interpolated_state = interpolator(a, b, t_abs);
      *out++ = interpolated_state;
      ++written;
      remaining -= (sample_density - carry);
      carry = 0.0;
    }
    carry += remaining;
  }

  *out++ = path_span.back();
  ++written;

  TRAILBLAZE_LOG_DBG(TLogger, ("resample: in=", path_span.size(), " out=", written,
                               " sample_density=", sample_density));
  return written;
}

// Use defaults provided by state_space<S>.
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
