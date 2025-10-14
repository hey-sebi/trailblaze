/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_SAMPLING_H_
#define TRAILBLAZE_SAMPLING_H_

#include <cstddef>

namespace trailblaze {
namespace sampling {

struct by_count {
  // number of states (>= 2 recommended)
  std::size_t n;
};

struct by_step {
  // desired spacing (meters or param delta)
  double step;
  // Note: generators will cap with total length/range.
};

} // namespace sampling
} // namespace trailblaze

#endif