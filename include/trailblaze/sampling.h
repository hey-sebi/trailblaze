/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstddef>

namespace trailblaze::sampling {

struct by_count {
  // number of states (>= 2 recommended)
  std::size_t n{2};
};

struct by_step {
  // desired spacing (meters or param delta)
  double step;
  // Note: generators will cap with total length/range.
};

} // namespace trailblaze::sampling
