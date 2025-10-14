/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_QUATERNION_H_
#define TRAILBLAZE_QUATERNION_H_

#include <cmath>

namespace trailblaze {

/** Quaternion type.
 *  Imaginary components are x, y, z, the real value component is w.
 */
struct quaternion {
  /// First imaginary component
  double x;
  /// Second imaginary component
  double y;
  /// Third imaginary component
  double z;
  /// Real value component.
  double w;
};

/** Scalar multiplication for quaternions.
 *  @param scalar The scalar value to multiply the quaternion with.
 *  @param q The quaternion value to multiply.
 *  @returns the multiplied quaternion.
 */
inline quaternion operator*(double scalar, const quaternion& q) {
  quaternion result;
  result.x = scalar * q.x;
  result.y = scalar * q.y;
  result.z = scalar * q.z;
  result.w = scalar * q.w;
  return result;
}

/** Scalar multiplication for quaternions.
 *  @param scalar The scalar value to multiply the quaternion with.
 *  @param q The quaternion value to multiply.
 *  @returns the multiplied quaternion.
 */
inline quaternion operator*(const quaternion& q, double scalar) {
  return scalar * q;
}

inline double squared_norm(const quaternion& q) {
  return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

inline double norm(const quaternion& q) {
  return std::sqrt(squared_norm(q));
}

inline void normalize(quaternion& q) {
  const double q_norm = norm(q);
  if (q_norm != 0.) {
    q = (1. / q_norm) * q;
  }
}

inline quaternion normalized(quaternion q) {
  quaternion q_normalized = q;
  normalize(q_normalized);
  return q_normalized;
}

} // namespace trailblaze

#endif