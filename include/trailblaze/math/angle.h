/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_MATH_ANGLE_H_
#define TRAILBLAZE_MATH_ANGLE_H_

#include <cmath>
#include <type_traits>

#include "trailblaze/math/numbers.h"

namespace trailblaze {

/** Converts an angle in degree to radians
 *  @param deg The angle having a value in degrees
 *  @returns The angle having a value in radians
 */
inline double to_rad(double deg) {
  return deg / 180. * numbers::pi;
}

/** Normalizes an angle to the range [-Pi, Pi).
 *  @tparam T Any floating point type
 *  @param angle Angle value in [rad]
 *  @returns the normalized angle
 */
template <typename T>
inline T normalized(const T angle) {
  static_assert(std::is_floating_point_v<T>, "normalized requires floating-point T");
  constexpr T two_pi = static_cast<T>(2.0) * static_cast<T>(numbers::pi);

  T x = std::fmod(angle + static_cast<T>(numbers::pi), two_pi);
  if (x < static_cast<T>(0)) {
    x += two_pi; // keep in [0, 2*Pi)
  }
  return x - static_cast<T>(numbers::pi);
}

/** Normalizes an angle to the range [-Pi, Pi)
 *  @tparam T Any floating point type
 *  @param angle Angle that is normalized, in [rad]
 */
template <typename T>
inline void normalize(T& angle) {
  angle = normalized(angle);
}

} // namespace trailblaze

#endif