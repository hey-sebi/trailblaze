/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// STL
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
  const quaternion q{1.0, 2.0, 3.0, 4.0};
  const double sq = squared_norm(q);
  EXPECT_DOUBLE_EQ(sq, 1.0 + 4.0 + 9.0 + 16.0); // 30
  const double n = norm(q);
  EXPECT_TRUE(nearly_equal(n, std::sqrt(30.0)));
}

TEST(QuaternionBasics, ScalingOperators) {
  const quaternion q{1.0, -2.0, 0.5, 3.0};
  const double s = 2.5;

  const quaternion left = s * q;
  const quaternion right = q * s;

  expect_quat_near(left, quaternion{s * q.x, s * q.y, s * q.z, s * q.w});
  expect_quat_near(right, left);
}

TEST(QuaternionNormalize, NormalizesToUnitLength) {
  quaternion q{1.0, 2.0, 3.0, 4.0};
  const double n = norm(q);
  ASSERT_GT(n, 0.0);

  quaternion expected{q.x / n, q.y / n, q.z / n, q.w / n};
  normalize(q);

  // Length is ~1
  EXPECT_TRUE(nearly_equal(norm(q), 1.0, 1e-12));
  // Direction preserved
  expect_quat_near(q, expected, 1e-12);
}

TEST(QuaternionNormalize, NoopOnZeroQuaternion) {
  quaternion q{0.0, 0.0, 0.0, 0.0};
  normalize(q);
  expect_quat_near(q, quaternion{0.0, 0.0, 0.0, 0.0});
  EXPECT_DOUBLE_EQ(squared_norm(q), 0.0);
}

TEST(QuaternionNormalize, StableForVerySmallMagnitude) {
  // Tiny values that would underflow if dividing by squared norm.
  quaternion q{1e-20, -1e-20, 2e-20, -2e-20};
  // Ensure it doesn't produce inf/NaN and ends up unit-length.
  normalize(q);
  EXPECT_TRUE(std::isfinite(q.x));
  EXPECT_TRUE(std::isfinite(q.y));
  EXPECT_TRUE(std::isfinite(q.z));
  EXPECT_TRUE(std::isfinite(q.w));
  EXPECT_TRUE(nearly_equal(norm(q), 1.0, 1e-12));
}

TEST(QuaternionNormalize, AlreadyUnitIsStable) {
  quaternion q{0.0, 0.0, 0.0, 1.0};
  normalize(q);
  expect_quat_near(q, quaternion{0.0, 0.0, 0.0, 1.0});
  EXPECT_TRUE(nearly_equal(norm(q), 1.0));
}

} // namespace trailblaze