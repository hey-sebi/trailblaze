#ifndef TRAILBLAZE_SPACE_O3_H_
#define TRAILBLAZE_SPACE_O3_H_

#include <algorithm>
#include <cmath>

#include "trailblaze/interpolation.h"

namespace trailblaze {

// -------------------- State --------------------
struct O3 {
  double qx;
  double qy;
  double qz;
  double qw;  // scalar last
};

// -------------------- Accessors --------------------
namespace access {
inline double& qx(O3& s) noexcept { return s.qx; }
inline double& qy(O3& s) noexcept { return s.qy; }
inline double& qz(O3& s) noexcept { return s.qz; }
inline double& qw(O3& s) noexcept { return s.qw; }
inline double qx(const O3& s) noexcept { return s.qx; }
inline double qy(const O3& s) noexcept { return s.qy; }
inline double qz(const O3& s) noexcept { return s.qz; }
inline double qw(const O3& s) noexcept { return s.qw; }
}  // namespace access

// -------------------- Atomic interpolator(s) --------------------
struct InterpQuatSlerp {
  template <typename S>
  void Apply(const S& a, const S& b, double t, S& out) const {
    // Requires S to have qx,qy,qz,qw — intended for O3 or types that embed it.
    double ax = a.qx, ay = a.qy, az = a.qz, aw = a.qw;
    double bx = b.qx, by = b.qy, bz = b.qz, bw = b.qw;

    double dot = ax * bx + ay * by + az * bz + aw * bw;
    if (dot < 0.0) {
      bx = -bx;
      by = -by;
      bz = -bz;
      bw = -bw;
      dot = -dot;
    }

    const double kEps = 1e-6;
    double sx, sy, sz, sw;
    if (dot > 1.0 - kEps) {
      sx = ax + (bx - ax) * t;
      sy = ay + (by - ay) * t;
      sz = az + (bz - az) * t;
      sw = aw + (bw - aw) * t;
    } else {
      const double theta = std::acos(std::max(-1.0, std::min(1.0, dot)));
      const double s = std::sin(theta);
      const double w1 = std::sin((1.0 - t) * theta) / s;
      const double w2 = std::sin(t * theta) / s;
      sx = ax * w1 + bx * w2;
      sy = ay * w1 + by * w2;
      sz = az * w1 + bz * w2;
      sw = aw * w1 + bw * w2;
    }
    const double n = std::sqrt(sx * sx + sy * sy + sz * sz + sw * sw);
    out.qx = sx / n;
    out.qy = sy / n;
    out.qz = sz / n;
    out.qw = sw / n;
  }
};

// (No default StateSpace binding for bare O3; it’s usually part of SE3.)

}  // namespace trailblaze

#endif  // TRAILBLAZE_SPACE_O3_H_
