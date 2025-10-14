/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_MATH_INTERPOLATION_H_
#define TRAILBLAZE_MATH_INTERPOLATION_H_

#include <algorithm>
#include <cmath>

#include "trailblaze/math/angle.h"
#include "trailblaze/quaternion.h"

namespace trailblaze {

/** Performs linear interpolation for scalar values.
 *  @tparam T Any floating point type
 *  @param a First value
 *  @param b Second value
 *  @param t Ratio used for interpolation. Will interpolate for 0 < t < 1.
 *         For t = 0, interpolation returns a.
 *         For t = 1, interpolation returns b.
 *         All other values extrapolate.
 *  @returns the interpolated value.
 */
struct scalar_interpolator {
  template <typename T>
  static T linear(const T& a, const T& b, double t) {
    static_assert(std::is_floating_point_v<T>,
                  "linear scalar interpolation requires floating-point T");
    return a + t * (b - a);
  }
};

/** Performs linear interpolation and normalization for radian angle values.
 *  @tparam T Any floating point type
 *  @param a First value
 *  @param b Second value
 *  @param t Ratio used for interpolation. Will interpolate for 0 < t < 1.
 *         For t = 0, interpolation returns a.
 *         For t = 1, interpolation returns b.
 *         All other values extrapolate.
 *  @returns the interpolated value.
 */
template <typename T>
T interpolate_angle_shortest(T a, T b, double t) {
  static_assert(std::is_floating_point_v<T>,
                "interpolate_angle_shortest requires floating-point T");
  double dist = normalized(b - a);
  return normalized(a + t * dist);
}

inline quaternion interpolate_quaternion(const quaternion& a, quaternion b, double t) {
  double dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  if (dot < 0.0) {
    b.x = -b.x;
    b.y = -b.y;
    b.z = -b.z;
    b.w = -b.w;
    dot = -dot;
  }

  constexpr double kEps = 1e-6;
  double           sx, sy, sz, sw;
  if (dot > 1.0 - kEps) {
    sx = a.x + (b.x - a.x) * t;
    sy = a.y + (b.y - a.y) * t;
    sz = a.z + (b.z - a.z) * t;
    sw = a.w + (b.w - a.w) * t;
  } else {
    const double theta = std::acos(std::max(-1.0, std::min(1.0, dot)));
    const double s     = std::sin(theta);
    const double w1    = std::sin((1.0 - t) * theta) / s;
    const double w2    = std::sin(t * theta) / s;
    sx                 = a.x * w1 + b.x * w2;
    sy                 = a.y * w1 + b.y * w2;
    sz                 = a.z * w1 + b.z * w2;
    sw                 = a.w * w1 + b.w * w2;
  }
  const double n = std::sqrt(sx * sx + sy * sy + sz * sz + sw * sw);

  quaternion out;
  out.x = sx / n;
  out.y = sy / n;
  out.z = sz / n;
  out.w = sw / n;
  return out;
}

} // namespace trailblaze

#endif