/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cmath>

#include "trailblaze/math/util.h"

namespace trailblaze {

/** Quaternion type.
 *  Imaginary components are x, y, z, the real value component is w.
 */
struct quaternion {
  /// First imaginary component
  double x{0.};
  /// Second imaginary component
  double y{0.};
  /// Third imaginary component
  double z{0.};
  /// Real value component.
  double w{1.};
};

/** Scalar multiplication for quaternions.
 *  @param lhs The scalar value to multiply the quaternion with.
 *  @param rhs The quaternion value to multiply.
 *  @returns the multiplied quaternion.
 */
inline quaternion operator*(double lhs, const quaternion& rhs) {
  quaternion result;
  result.x = lhs * rhs.x;
  result.y = lhs * rhs.y;
  result.z = lhs * rhs.z;
  result.w = lhs * rhs.w;
  return result;
}

/** Scalar multiplication for quaternions.
 *  @param lhs The quaternion value to multiply.
 *  @param rhs The scalar value to multiply the quaternion with.
 *  @returns the multiplied quaternion.
 */
inline quaternion operator*(const quaternion& lhs, double rhs) {
  return rhs * lhs;
}

inline double squared_norm(const quaternion& q) {
  return square(q.x) + square(q.y) + square(q.z) + square(q.w);
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

inline quaternion normalized(const quaternion& q) {
  quaternion q_normalized = q;
  normalize(q_normalized);
  return q_normalized;
}

} // namespace trailblaze
