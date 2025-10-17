/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// STL
#include <algorithm>
#include <cmath>
// external
#include <gtest/gtest.h>

#include "trailblaze/quaternion.h"

namespace {

bool nearly_equal(double a, double b, double tol = 1e-12) {
  return std::fabs(a - b) <= tol * std::max(1.0, std::max(std::fabs(a), std::fabs(b)));
}

void expect_quat_near(const trailblaze::quaternion& a, const trailblaze::quaternion& b,
                      double tol = 1e-12) {
  EXPECT_TRUE(nearly_equal(a.x, b.x, tol)) << "x: " << a.x << " vs " << b.x;
  EXPECT_TRUE(nearly_equal(a.y, b.y, tol)) << "y: " << a.y << " vs " << b.y;
  EXPECT_TRUE(nearly_equal(a.z, b.z, tol)) << "z: " << a.z << " vs " << b.z;
  EXPECT_TRUE(nearly_equal(a.w, b.w, tol)) << "w: " << a.w << " vs " << b.w;
}

} // namespace

namespace trailblaze {

TEST(QuaternionBasics, SquaredNormAndNorm) {
  const quaternion quat{1.0, 2.0, 3.0, 4.0};
  const double sq_quat_norm = squared_norm(quat);
  EXPECT_DOUBLE_EQ(sq_quat_norm, 1.0 + 4.0 + 9.0 + 16.0); // 30
  const double quat_norm = norm(quat);
  EXPECT_TRUE(nearly_equal(quat_norm, std::sqrt(30.0)));
}

TEST(QuaternionBasics, ScalingOperators) {
  const quaternion quat{1.0, -2.0, 0.5, 3.0};
  const double scalar = 2.5;

  const quaternion left = scalar * quat;
  const quaternion right = quat * scalar;

  expect_quat_near(left,
                   quaternion{scalar * quat.x, scalar * quat.y, scalar * quat.z, scalar * quat.w});
  expect_quat_near(right, left);
}

TEST(QuaternionNormalize, NormalizesToUnitLength) {
  quaternion quat{1.0, 2.0, 3.0, 4.0};
  const double quat_norm = norm(quat);
  ASSERT_GT(quat_norm, 0.0);

  quaternion expected{quat.x / quat_norm, quat.y / quat_norm, quat.z / quat_norm,
                      quat.w / quat_norm};
  normalize(quat);

  // Length is ~1
  EXPECT_TRUE(nearly_equal(norm(quat), 1.0, 1e-12));
  // Direction is preserved
  expect_quat_near(quat, expected, 1e-12);
}

TEST(QuaternionNormalize, NoopOnZeroQuaternion) {
  quaternion quat{0.0, 0.0, 0.0, 0.0};
  normalize(quat);
  expect_quat_near(quat, quaternion{0.0, 0.0, 0.0, 0.0});
  EXPECT_DOUBLE_EQ(squared_norm(quat), 0.0);
}

TEST(QuaternionNormalize, StableForVerySmallMagnitude) {
  // Tiny values that would underflow if dividing by squared norm.
  quaternion quat{1e-20, -1e-20, 2e-20, -2e-20};
  // Ensure it doesn't produce inf/NaN and ends up unit-length.
  normalize(quat);
  EXPECT_TRUE(std::isfinite(quat.x));
  EXPECT_TRUE(std::isfinite(quat.y));
  EXPECT_TRUE(std::isfinite(quat.z));
  EXPECT_TRUE(std::isfinite(quat.w));
  EXPECT_TRUE(nearly_equal(norm(quat), 1.0, 1e-12));
}

TEST(QuaternionNormalize, AlreadyUnitIsStable) {
  quaternion quat{0.0, 0.0, 0.0, 1.0};
  normalize(quat);
  expect_quat_near(quat, quaternion{0.0, 0.0, 0.0, 1.0});
  EXPECT_TRUE(nearly_equal(norm(quat), 1.0));
}

} // namespace trailblaze