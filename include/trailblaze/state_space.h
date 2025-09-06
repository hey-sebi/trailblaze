#ifndef TRAILBLAZE_STATE_SPACE_H_
#define TRAILBLAZE_STATE_SPACE_H_

namespace trailblaze {

// Primary template. Specialize per state type to set defaults.
template <typename S>
struct StateSpace {
  // using Metric = ...;
  // using Interp = ...;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_STATE_SPACE_H_
