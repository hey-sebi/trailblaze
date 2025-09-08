#ifndef TRAILBLAZE_MATH_ANGLE_H_
#define TRAILBLAZE_MATH_ANGLE_H_

#include <cmath>
#include <type_traits>

namespace trailblaze {

/** Converts an angle in degree to radians
 *  @param deg The angle having a value in degrees
 *  @returns The angle having a value in radians
 */
inline double ToRad(double deg)
{
  return deg / 180. * M_PI;
}

/** Normalizes an angle to the range (-Pi, Pi].
 *  @tparam Any floating point type
 *  @param angle Angle value in [rad]
 *  @returns the normalized angle
 */
template <typename T>
inline T NormalizeAngle(T angle)
{
  static_assert(std::is_floating_point_v<T>, "NormalizeAngle requires floating-point T");

  while (angle < -M_PI)
  {
    angle += 2 * M_PI;
  }
  while (angle >= M_PI)
  {
    angle -= 2 * M_PI;
  }
  return angle;
}

}  // namespace trailblaze

#endif