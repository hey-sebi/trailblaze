#ifndef TRAILBLAZE_ANNOTATE_H_
#define TRAILBLAZE_ANNOTATE_H_

#include <algorithm>
#include <cmath>
#include <vector>

#include "trailblaze/math/angle.h"
#include "trailblaze/space_r2.h"
#include "trailblaze/space_se2.h"

namespace trailblaze {
namespace annotate {

/** @brief Add yaw using forward chord (next - current). Last uses backward chord.
 *
 *  With this, orientations follow an approximative pseudo-tangent on the path. The
 *  orientations will be more exact for paths that are dense.
 */
inline std::vector<SE2> YawChord(const std::vector<R2>& r2)
{
  std::vector<SE2> out;
  if (r2.empty())
  {
    return out;
  }
  out.reserve(r2.size());

  const auto yaw_of = [](const R2& a, const R2& b) {
    return std::atan2(b.y - a.y, b.x - a.x);
  };

  if (r2.size() == 1)
  {
    out.push_back({r2[0].x, r2[0].y, 0.0});
    return out;
  }

  for (std::size_t i = 0; i < r2.size(); ++i)
  {
    double yaw = 0.0;
    if (i + 1 < r2.size())
    {
      // forward difference
      yaw = yaw_of(r2[i], r2[i + 1]);
    }
    else
    {
      // backward difference
      yaw = yaw_of(r2[i - 1], r2[i]);
    }
    out.push_back({r2[i].x, r2[i].y, NormalizedAngle(yaw)});
  }
  return out;
}

/** @brief Add yaw using centered finite differences (proper tangent).
 *
 *
 */
inline std::vector<SE2> YawCenteredDiff(const std::vector<R2>& r2)
{
  std::vector<SE2> out;
  if (r2.empty())
  {
    return out;
  }
  if (r2.size() == 1)
  {
    out.push_back({r2[0].x, r2[0].y, 0.0});
    return out;
  }
  out.reserve(r2.size());

  const auto yaw_of = [](const R2& a, const R2& b) {
    return std::atan2(b.y - a.y, b.x - a.x);
  };

  for (std::size_t i = 0; i < r2.size(); ++i)
  {
    double yaw = 0.0;
    if (i == 0)
    {
      yaw = yaw_of(r2[0], r2[1]);  // forward at start
    }
    else if (i + 1 == r2.size())
    {
      yaw = yaw_of(r2[i - 1], r2[i]);  // backward at end
    }
    else
    {
      yaw = yaw_of(r2[i - 1], r2[i + 1]);  // centered
    }
    out.push_back({r2[i].x, r2[i].y, NormalizedAngle(yaw)});
  }
  return out;
}

/** @brief Attach yaw by linear interpolation between start_yaw and end_yaw.
 *
 *
 */
inline std::vector<SE2> YawLerp(const std::vector<R2>& r2, double start_yaw,
                                double end_yaw)
{
  std::vector<SE2> out;
  out.reserve(r2.size());
  if (r2.empty())
    return out;

  // Shortest angular interpolation
  double d = NormalizedAngle(end_yaw - start_yaw);
  for (std::size_t i = 0; i < r2.size(); ++i)
  {
    double t = (r2.size() == 1) ? 0.0 : static_cast<double>(i) / (r2.size() - 1);
    double yaw = NormalizedAngle(start_yaw + t * d);
    out.push_back({r2[i].x, r2[i].y, yaw});
  }
  return out;
}

/** @brief Attach a constant yaw.
 *
 */
inline std::vector<SE2> YawConstant(const std::vector<R2>& r2, double yaw)
{
  std::vector<SE2> out;
  out.reserve(r2.size());
  for (const auto& p : r2)
  {
    out.push_back({p.x, p.y, NormalizedAngle(yaw)});
  }
  return out;
}

}  // namespace annotate
}  // namespace trailblaze
#endif