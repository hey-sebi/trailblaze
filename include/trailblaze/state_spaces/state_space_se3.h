#ifndef TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE3_H_
#define TRAILBLAZE_STATE_SPACES_STATE_SPACE_SE3_H_

#include <cmath>

#include "trailblaze/interpolation.h"
#include "trailblaze/state_space.h"
#include "trailblaze/state_spaces/state_space_o3.h"
#include "trailblaze/state_spaces/state_space_r3.h"

namespace trailblaze {

/// Models a state belonging to the StateSpaceSE3
struct StateSe3
{
  R3 position;
  O3 orientation;
};

// ------------ component-wise accessors  -----------------
namespace comp {

inline double& x(StateSe3& s) noexcept
{
  return s.position.x;
}

inline double& y(StateSe3& s) noexcept
{
  return s.position.y;
}

inline double& z(StateSe3& s) noexcept
{
  return s.position.z;
}

inline double x(const StateSe3& s) noexcept
{
  return s.position.x;
}

inline double y(const StateSe3& s) noexcept
{
  return s.position.y;
}

inline double z(const StateSe3& s) noexcept
{
  return s.position.z;
}

inline double& qx(StateSe3& s) noexcept
{
  return s.orientation.qx;
}

inline double& qy(StateSe3& s) noexcept
{
  return s.orientation.qy;
}

inline double& qz(StateSe3& s) noexcept
{
  return s.orientation.qz;
}

inline double& qw(StateSe3& s) noexcept
{
  return s.orientation.qw;
}

inline double qx(const StateSe3& s) noexcept
{
  return s.orientation.qx;
}

inline double qy(const StateSe3& s) noexcept
{
  return s.orientation.qy;
}

inline double qz(const StateSe3& s) noexcept
{
  return s.orientation.qz;
}

inline double qw(const StateSe3& s) noexcept
{
  return s.orientation.qw;
}

}  // namespace comp

struct MetricSe3
{
  double operator()(const StateSe3& a, const StateSe3& b) const
  {
    // TODO: also consider orientation
    const double dx = a.position.x - b.position.x;
    const double dy = a.position.y - b.position.y;
    const double dz = a.position.z - b.position.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
};

// Optional: weighted orientation-aware metric.
struct MetricSe3Weighted
{
  explicit MetricSe3Weighted(double w_ang) : w_ang_(w_ang)
  {
  }

  double operator()(const StateSe3& a, const StateSe3& b) const
  {
    const double dx = a.position.x - b.position.x;
    const double dy = a.position.y - b.position.y;
    const double dz = a.position.z - b.position.z;
    const double dpos = std::sqrt(dx * dx + dy * dy + dz * dz);
    // Angular distance via quaternion dot.
    const double dot =
        a.orientation.qx * b.orientation.qx + a.orientation.qy * b.orientation.qy +
        a.orientation.qz * b.orientation.qz + a.orientation.qw * b.orientation.qw;
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
