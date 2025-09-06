#ifndef TRAILBLAZE_ALG_RESAMPLE_H_
#define TRAILBLAZE_ALG_RESAMPLE_H_

#include <cstddef>
#include <limits>

#include "trailblaze/logging.h"
#include "trailblaze/span.h"
#include "trailblaze/state_space.h"

namespace trailblaze {

// State-agnostic resampler: you inject Metric and Interp policies.
// Metric:  double operator()(const S& a, const S& b) const;
// Interp:  S operator()(const S& a, const S& b, double t) const;
template <typename Logger, typename S, typename Metric, typename Interp,
          typename OutIt>
std::size_t Resample(Span<const S> p, double ds, OutIt out, Metric metric,
                     Interp interp) {
  if (p.size() == 0) return 0;
  if (p.size() == 1) {
    *out++ = p[0];
    return 1;
  }
  if (ds <= 0) {
    PATH_LOG_DBG(Logger, ("Resample: nonpositive ds"));
    *out++ = p.front();
    *out++ = p.back();
    return 2;
  }

  *out++ = p.front();
  std::size_t written = 1;

  double carry = 0.0;
  for (std::size_t i = 1; i < p.size(); ++i) {
    const S& a = p[i - 1];
    const S& b = p[i];

    const double seg = metric(a, b);
    if (seg <= std::numeric_limits<double>::epsilon()) {
      continue;
    }

    double remaining = seg;
    while (carry + remaining >= ds) {
      // absolute t in [0,1] along the current segment
      const double t_abs = 1.0 - (remaining - (ds - carry)) / seg;
      S s = interp(a, b, t_abs);
      *out++ = s;
      ++written;
      remaining -= (ds - carry);
      carry = 0.0;
    }
    carry += remaining;
  }

  *out++ = p.back();
  ++written;

  PATH_LOG_DBG(Logger,
               ("Resample: in=", p.size(), " out≈", written, " ds=", ds));
  return written;
}

// Sugar: use defaults provided by StateSpace<S>.
template <typename Logger, typename S, typename OutIt>
std::size_t Resample(Span<const S> p, double ds, OutIt out) {
  using Metric = typename StateSpace<S>::Metric;
  using Interp = typename StateSpace<S>::Interp;
  return Resample<Logger>(p, ds, out, Metric{}, Interp{});
}

}  // namespace trailblaze

#endif  // TRAILBLAZE_ALG_RESAMPLE_H_
