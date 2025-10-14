/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_ALG_RESAMPLE_H_
#define TRAILBLAZE_ALG_RESAMPLE_H_

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
template <typename TLogger,
          typename TState,
          typename TMetric,
          typename TInterpolation,
          typename OutIt>
std::size_t
resample(span<const TState> p, double ds, OutIt out, TMetric metric, TInterpolation interpolator) {
  if (p.size() == 0) {
    return 0;
  }
  if (p.size() == 1) {
    *out++ = p[0];
    return 1;
  }
  if (ds <= 0) {
    TRAILBLAZE_LOG_DBG(TLogger, ("resample: nonpositive ds"));
    *out++ = p.front();
    *out++ = p.back();
    return 2;
  }

  *out++              = p.front();
  std::size_t written = 1;

  double carry = 0.0;
  for (std::size_t i = 1; i < p.size(); ++i) {
    const TState& a = p[i - 1];
    const TState& b = p[i];

    const double seg = metric(a, b);
    if (seg <= std::numeric_limits<double>::epsilon()) {
      continue;
    }

    double remaining = seg;
    while (carry + remaining >= ds) {
      // absolute t in [0,1] along the current segment
      const double t_abs = 1.0 - (remaining - (ds - carry)) / seg;
      TState       s     = interpolator(a, b, t_abs);
      *out++             = s;
      ++written;
      remaining -= (ds - carry);
      carry = 0.0;
    }
    carry += remaining;
  }

  *out++ = p.back();
  ++written;

  TRAILBLAZE_LOG_DBG(TLogger, ("resample: in=", p.size(), " out=", written, " ds=", ds));
  return written;
}

// Use defaults provided by state_space<S>.
template <typename TLogger, typename TState, typename OutIt>
std::size_t resample(span<const TState> p, double ds, OutIt out) {
  using TMetric        = typename state_space<TState>::TMetric;
  using TInterpolation = typename state_space<TState>::TInterpolation;
  return resample<TLogger>(p, ds, out, TMetric{}, TInterpolation{});
}

// forwarding overload to help template deduction when caller has span<TState>.
template <typename TLogger,
          typename TState,
          typename TMetric,
          typename TInterpolation,
          typename OutIt>
std::size_t
resample(span<TState> p, double ds, OutIt out, TMetric metric, TInterpolation interpolator) {
  using Base = std::remove_const_t<TState>;
  // Build a span<const Base> from pointer+size (works with your minimal span)
  return resample<TLogger>(span<const Base>(static_cast<const Base*>(p.data()), p.size()),
                           ds,
                           out,
                           metric,
                           interpolator);
}

// forwarding overload using state_space Metric and Interpolation
template <typename TLogger, typename TState, typename OutIt>
std::size_t resample(span<TState> path_span, double ds, OutIt out) {
  using StateBase      = std::remove_const_t<TState>;
  using TMetric        = typename state_space<StateBase>::metric_type;
  using TInterpolation = typename state_space<StateBase>::interpolation_type;
  return resample<TLogger>(
      span<const StateBase>(static_cast<const StateBase*>(path_span.data()), path_span.size()),
      ds,
      out,
      TMetric{},
      TInterpolation{});
}

} // namespace trailblaze

#endif
