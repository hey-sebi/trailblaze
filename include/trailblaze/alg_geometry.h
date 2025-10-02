/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_ALG_GEOMETRY_H_
#define TRAILBLAZE_ALG_GEOMETRY_H_

#include <cmath>

#include "trailblaze/backport/span.h"
#include "trailblaze/state_traits.h"

namespace trailblaze {

/** Computes the length of a path or a path segment.
 *  Considers only X and Y components of the state space.
 *
 *  @tparam TState State that has X and Y components.
 *
 *  @param path_span Path or path segment for which to compute the length.
 *  @returns the length.
 */
template <typename TState>
double LengthXy(Span<const TState> path_span)
{
  static_assert(StateTraits<TState>::kHasXy,
                "LengthXy: TState must have components x & y");
  if (path_span.size() < 2)
  {
    return 0.0;
  }
  double length = 0.0;
  for (std::size_t i = 1; i < path_span.size(); ++i)
  {
    const double dx = path_span[i].x - path_span[i - 1].x;
    const double dy = path_span[i].y - path_span[i - 1].y;
    length += std::hypot(dx, dy);
  }
  return length;
}

template <typename Logger, typename StateR3>
void NormalizeYaw(Span<StateR3> p)
{
  static_assert(StateTraits<StateR3>::kHasYaw, "NormalizeYaw: S must have member yaw");
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

#endif
