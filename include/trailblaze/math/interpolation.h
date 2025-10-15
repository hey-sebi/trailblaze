/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <algorithm>
#include <cmath>

#include "trailblaze/constants.h"
#include "trailblaze/math/angle.h"
#include "trailblaze/math/util.h"
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

  double interpol_x = 0.;
  double interpol_y = 0.;
  double interpol_z = 0.;
  double interpol_w = 0.;

  if (dot > 1.0 - constants::quaternion_interpolation_epsilon) {
    interpol_x = a.x + (b.x - a.x) * t;
    interpol_y = a.y + (b.y - a.y) * t;
    interpol_z = a.z + (b.z - a.z) * t;
    interpol_w = a.w + (b.w - a.w) * t;
  } else {
    const double theta = std::acos(std::max(-1.0, std::min(1.0, dot)));
    const double sin_theta = std::sin(theta);
    const double weight1 = std::sin((1.0 - t) * theta) / sin_theta;
    const double weight2 = std::sin(t * theta) / sin_theta;

    interpol_x = a.x * weight1 + b.x * weight2;
    interpol_y = a.y * weight1 + b.y * weight2;
    interpol_z = a.z * weight1 + b.z * weight2;
    interpol_w = a.w * weight1 + b.w * weight2;
  }
  const double n =
      std::sqrt(square(interpol_x) + square(interpol_y) + square(interpol_z) + square(interpol_w));

  quaternion out;
  out.x = interpol_x / n;
  out.y = interpol_y / n;
  out.z = interpol_z / n;
  out.w = interpol_w / n;
  return out;
}

} // namespace trailblaze
