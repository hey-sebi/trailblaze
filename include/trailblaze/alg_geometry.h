#ifndef TRAILBLAZE_ALG_GEOMETRY_H_
#define TRAILBLAZE_ALG_GEOMETRY_H_

#include <cmath>

#include "trailblaze/backport/span.h"
#include "trailblaze/state_traits.h"

// Note: XY utilities require accessors from space_r2.h (included by users who
// call these). We keep these algorithms lightweight and traits-guarded.

namespace trailblaze {

// Requires S to expose x,y members (flat types) or ensure accessors exist if
// you adapt this to use accessors instead.
template <typename S>
double LengthXy(Span<const S> p)
{
  static_assert(StateTraits<S>::kHasXy, "LengthXy: S must have members x,y");
  if (p.size() < 2)
    return 0.0;
  double L = 0.0;
  for (std::size_t i = 1; i < p.size(); ++i)
  {
    const double dx = p[i].x - p[i - 1].x;
    const double dy = p[i].y - p[i - 1].y;
    L += std::hypot(dx, dy);
  }
  return L;
}

template <typename Logger, typename S>
void NormalizeYaw(Span<S> p)
{
  static_assert(StateTraits<S>::kHasYaw, "NormalizeYaw: S must have member yaw");
  TRAILBLAZE_LOG_DBG(Logger, ("NormalizeYaw: N=", p.size()));
  constexpr double kPi = 3.141592653589793238462643383279502884;
  constexpr double kTwoPi = 2.0 * kPi;
  for (auto& s : p)
  {
    double y = s.yaw;
    if (y >= kPi || y < -kPi)
    {
      y = std::fmod(y + kPi, kTwoPi);
      if (y < 0)
        y += kTwoPi;
      y -= kPi;
      s.yaw = y;
    }
  }
}

}  // namespace trailblaze

#endif  // TRAILBLAZE_ALG_GEOMETRY_H_
