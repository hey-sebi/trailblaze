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

bool NearlyEqual(double a, double b, double tol = 1e-12) {
  return std::fabs(a - b) <= tol * std::max(1.0, std::max(std::fabs(a), std::fabs(b)));
}

void ExpectQuatNear(const trailblaze::Quaternion& a,
                    const trailblaze::Quaternion& b,
                    double                        tol = 1e-12) {
  EXPECT_TRUE(NearlyEqual(a.x, b.x, tol)) << "x: " << a.x << " vs " << b.x;
  EXPECT_TRUE(NearlyEqual(a.y, b.y, tol)) << "y: " << a.y << " vs " << b.y;
  EXPECT_TRUE(NearlyEqual(a.z, b.z, tol)) << "z: " << a.z << " vs " << b.z;
  EXPECT_TRUE(NearlyEqual(a.w, b.w, tol)) << "w: " << a.w << " vs " << b.w;
}

} // namespace

namespace trailblaze {

TEST(QuaternionBasics, SquaredNormAndNorm) {
  const Quaternion q{1.0, 2.0, 3.0, 4.0};
  const double     sq = SquaredNorm(q);
  EXPECT_DOUBLE_EQ(sq, 1.0 + 4.0 + 9.0 + 16.0); // 30
  const double n = Norm(q);
  EXPECT_TRUE(NearlyEqual(n, std::sqrt(30.0)));
}

TEST(QuaternionBasics, ScalingOperators) {
  const Quaternion q{1.0, -2.0, 0.5, 3.0};
  const double     s = 2.5;

  const Quaternion left  = s * q;
  const Quaternion right = q * s;

  ExpectQuatNear(left, Quaternion{s * q.x, s * q.y, s * q.z, s * q.w});
  ExpectQuatNear(right, left);
}

TEST(QuaternionNormalize, NormalizesToUnitLength) {
  Quaternion   q{1.0, 2.0, 3.0, 4.0};
  const double n = Norm(q);
  ASSERT_GT(n, 0.0);

  Quaternion expected{q.x / n, q.y / n, q.z / n, q.w / n};
  Normalize(q);

  // Length is ~1
  EXPECT_TRUE(NearlyEqual(Norm(q), 1.0, 1e-12));
  // Direction preserved
  ExpectQuatNear(q, expected, 1e-12);
}

TEST(QuaternionNormalize, NoopOnZeroQuaternion) {
  Quaternion q{0.0, 0.0, 0.0, 0.0};
  Normalize(q);
  ExpectQuatNear(q, Quaternion{0.0, 0.0, 0.0, 0.0});
  EXPECT_DOUBLE_EQ(SquaredNorm(q), 0.0);
}

TEST(QuaternionNormalize, StableForVerySmallMagnitude) {
  // Tiny values that would underflow if dividing by squared norm.
  Quaternion q{1e-20, -1e-20, 2e-20, -2e-20};
  // Ensure it doesn't produce inf/NaN and ends up unit-length.
  Normalize(q);
  EXPECT_TRUE(std::isfinite(q.x));
  EXPECT_TRUE(std::isfinite(q.y));
  EXPECT_TRUE(std::isfinite(q.z));
  EXPECT_TRUE(std::isfinite(q.w));
  EXPECT_TRUE(NearlyEqual(Norm(q), 1.0, 1e-12));
}

TEST(QuaternionNormalize, AlreadyUnitIsStable) {
  Quaternion q{0.0, 0.0, 0.0, 1.0};
  Normalize(q);
  ExpectQuatNear(q, Quaternion{0.0, 0.0, 0.0, 1.0});
  EXPECT_TRUE(NearlyEqual(Norm(q), 1.0));
}

} // namespace trailblaze