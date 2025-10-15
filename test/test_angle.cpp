/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// external
#include <gtest/gtest.h>

#include "trailblaze/backport/numbers.h"
#include "trailblaze/math/angle.h"
#include "trailblaze/math/numbers.h"

namespace trailblaze {

TEST(Angle, DegToRadConversion) {
  EXPECT_DOUBLE_EQ(to_rad(0.), 0);
  EXPECT_DOUBLE_EQ(to_rad(90.), numbers::pi_2);
  EXPECT_DOUBLE_EQ(to_rad(-90.), -numbers::pi_2);
  EXPECT_DOUBLE_EQ(to_rad(180.), numbers::pi);
}

// Fixture for parameterized normalization test
class angle_normalization : public ::testing::TestWithParam<double> {};

TEST_P(angle_normalization, NormalizedAngleIsInTargetRange) {
  double angle = GetParam();
  double normalized_angle = normalized(angle);

  EXPECT_GE(normalized_angle, -numbers::pi);
  EXPECT_LT(normalized_angle, numbers::pi);
}

INSTANTIATE_TEST_SUITE_P(RadianSamples, angle_normalization,
                         ::testing::Values(-100.0, -3.14, -1.57, 0.0, 1.0, 1.57, 3.14, 42.0,
                                           100.0));

} // namespace trailblaze