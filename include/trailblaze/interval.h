
/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <stdexcept>

namespace trailblaze {

/// Models an interval. Bounds are included.
template <typename T>
struct interval {
  /** Constructor
   *  @param lower The lower bound of the interval.
   *  @param upper The upper bound of the interval.
   *  @throws std::invalid_argument if @p lower > upper.
   */
  interval(const T& lower, const T& upper) // NOLINT
      : lower_bound(lower), upper_bound(upper) {
    if (lower > upper) {
      throw std::invalid_argument("lower bound of the interval is greater than the upper bound!");
    }
  }

  /// The lower bound of the interval.
  T lower_bound;
  /// The upper bound of the interval.
  T upper_bound;
};

} // namespace trailblaze