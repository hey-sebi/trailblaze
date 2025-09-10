#ifndef TRAILBLAZE_SAMPLING_H_
#define TRAILBLAZE_SAMPLING_H_
#include <cstddef>

namespace trailblaze {
namespace sampling {

struct ByCount
{
  // number of states (>= 2 recommended)
  std::size_t n;
};

struct ByStep
{
  // desired spacing (meters or param delta)
  double step;
  // Note: generators will cap with total length/range.
};

}  // namespace sampling
}  // namespace trailblaze

#endif