#ifndef TRAILBLAZE_SPACE_SE3_H_
#define TRAILBLAZE_SPACE_SE3_H_

#include <cmath>

#include "trailblaze/interpolation.h"
#include "trailblaze/space_o3.h"
#include "trailblaze/space_r3.h"
#include "trailblaze/state_space.h"

namespace trailblaze {

// -------------------- State (composition of atoms) --------------------
struct SE3
{
  R3 pos;
  O3 ori;
};

// -------------------- Accessors --------------------
namespace access {
inline double& x(SE3& s) noexcept
{
  return s.pos.x;
}

inline double& y(SE3& s) noexcept
{
  return s.pos.y;
}

inline double& z(SE3& s) noexcept
{
  return s.pos.z;
}

inline double x(const SE3& s) noexcept
{
  return s.pos.x;
}

inline double y(const SE3& s) noexcept
{
  return s.pos.y;
}

inline double z(const SE3& s) noexcept
{
  return s.pos.z;
}

inline double& qx(SE3& s) noexcept
{
  return s.ori.qx;
}

inline double& qy(SE3& s) noexcept
{
  return s.ori.qy;
}

inline double& qz(SE3& s) noexcept
{
  return s.ori.qz;
}

inline double& qw(SE3& s) noexcept
{
  return s.ori.qw;
}

inline double qx(const SE3& s) noexcept
{
  return s.ori.qx;
}

inline double qy(const SE3& s) noexcept
{
  return s.ori.qy;
}

inline double qz(const SE3& s) noexcept
{
  return s.ori.qz;
}

inline double qw(const SE3& s) noexcept
{
  return s.ori.qw;
}
}  // namespace access

// -------------------- Metric(s) --------------------
// Default: positional arc-length only (common for spacing).
struct MetricSe3Pos
{
  double operator()(const SE3& a, const SE3& b) const
  {
    const double dx = a.pos.x - b.pos.x;
    const double dy = a.pos.y - b.pos.y;
    const double dz = a.pos.z - b.pos.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
};

// Optional: weighted orientation-aware metric.
struct MetricSe3Weighted
{
  explicit MetricSe3Weighted(double w_ang) : w_ang_(w_ang)
  {
  }

  double operator()(const SE3& a, const SE3& b) const
  {
    const double dx = a.pos.x - b.pos.x;
    const double dy = a.pos.y - b.pos.y;
    const double dz = a.pos.z - b.pos.z;
    const double dpos = std::sqrt(dx * dx + dy * dy + dz * dz);
    // Angular distance via quaternion dot.
    const double dot = a.ori.qx * b.ori.qx + a.ori.qy * b.ori.qy + a.ori.qz * b.ori.qz +
                       a.ori.qw * b.ori.qw;
    const double ang = 2.0 * std::acos(std::min(1.0, std::abs(dot)));
    return std::sqrt(dpos * dpos + (w_ang_ * ang) * (w_ang_ * ang));
  }

 private:
  double w_ang_;
};

// -------------------- Atomic interpolator(s) --------------------
struct InterpSe3Pos
{
  void Apply(const SE3& a, const SE3& b, double t, SE3& out) const
  {
    out.pos.x = LerpScalar::Lerp(a.pos.x, b.pos.x, t);
    out.pos.y = LerpScalar::Lerp(a.pos.y, b.pos.y, t);
    out.pos.z = LerpScalar::Lerp(a.pos.z, b.pos.z, t);
  }
};

struct InterpSe3QuatSlerp
{
  void Apply(const SE3& a, const SE3& b, double t, SE3& out) const
  {
    // Reuse O3 slerp on the embedded quaternions.
    O3 tmp_a = a.ori;
    O3 tmp_b = b.ori;
    O3 tmp_out = out.ori;
    InterpQuatSlerp{}.Apply(tmp_a, tmp_b, t, tmp_out);
    out.ori = tmp_out;
  }
};

// Compose full SE3 interpolation (position + orientation).
using InterpSe3Full = ComposeInterp<InterpSe3Pos, InterpSe3QuatSlerp>;

// -------------------- Defaults binding --------------------
template <typename S>
struct StateSpace;  // NOLINT

template <>
struct StateSpace<SE3>
{
  using Metric = MetricSe3Pos;   // default to position-only spacing
  using Interp = InterpSe3Full;  // position + quaternion slerp
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_SE3_H_
