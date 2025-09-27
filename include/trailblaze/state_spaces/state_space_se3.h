#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE3_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE3_H_

#include <cmath>

// #include "trailblaze/interpolation.h"
#include "trailblaze/state_space.h"
#include "trailblaze/state_spaces/state_space_r3.h"
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceSE3
struct StateSe3
{
  StateR3 position;
  Quaternion orientation;
};

// Weighted, orientation-aware metric.
struct MetricSe3Weighted
{
  explicit MetricSe3Weighted(double w_ang) : w_ang_(w_ang)
  {
  }

  double operator()(const StateSe3& a, const StateSe3& b) const
  {
    const double dpos = EuclideanDistance3D::Calculate(a, b);
    // Angular distance via quaternion dot.
    const double dot =
        a.orientation.x * b.orientation.x + a.orientation.y * b.orientation.y +
        a.orientation.z * b.orientation.z + a.orientation.w * b.orientation.w;
    const double ang = 2.0 * std::acos(std::min(1.0, std::abs(dot)));
    return std::sqrt(dpos * dpos + (w_ang_ * ang) * (w_ang_ * ang));
  }

 private:
  double w_ang_;
};

struct InterpolatePositionSe3
{
  void Apply(const StateSe3& a, const StateSe3& b, double t, StateSe3& out) const
  {
    out.position.x = LerpScalar::Lerp(a.position.x, b.position.x, t);
    out.position.y = LerpScalar::Lerp(a.position.y, b.position.y, t);
    out.position.z = LerpScalar::Lerp(a.position.z, b.position.z, t);
  }
};

struct InterpolateOrientationSe3
{
  void Apply(const StateSe3& a, const StateSe3& b, double t, StateSe3& out) const
  {
    InterpQuatSlerp{}.Apply(a.orientation, b.orientation, t, out.orientation);
  }
};

using InterpolateSe3 = ComposeInterp<InterpSe3Pos, InterpSe3QuatSlerp>;

template <typename TState>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<StateSe3>
{
  using Metric = MetricSe3;
  using Interpolation = InterpolateSe3;
};

}  // namespace trailblaze

#endif
