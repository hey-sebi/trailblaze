/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// external
#include <gtest/gtest.h>

#include "trailblaze/math/angle.h"

namespace trailblaze {

TEST(Angle, DegToRadConversion) {
  EXPECT_DOUBLE_EQ(ToRad(0.), 0);
  EXPECT_DOUBLE_EQ(ToRad(90.), M_PI_2);
  EXPECT_DOUBLE_EQ(ToRad(-90.), -M_PI_2);
  EXPECT_DOUBLE_EQ(ToRad(180.), M_PI);
}

// Fixture for parameterized normalization test
class AngleNormalization : public ::testing::TestWithParam<double> {};

TEST_P(AngleNormalization, NormalizedAngleIsInTargetRange) {
  double angle            = GetParam();
  double normalized_angle = NormalizedAngle(angle);

  EXPECT_GE(normalized_angle, -M_PI);
  EXPECT_LT(normalized_angle, M_PI);
}

INSTANTIATE_TEST_SUITE_P(
    RadianSamples,
    AngleNormalization,
    ::testing::Values(-100.0, -3.14, -1.57, 0.0, 1.0, 1.57, 3.14, 42.0, 100.0));

} // namespace trailblaze