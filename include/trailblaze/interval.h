
/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

namespace trailblaze {

template <typename T>
struct interval {
  interval(const T& lower, const T& upper) : lower_bound(lower), upper_bound(upper) {}
  T lower_bound;
  T upper_bound;
};

} // namespace trailblaze