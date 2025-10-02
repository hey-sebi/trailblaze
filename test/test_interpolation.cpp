/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// external
#include <gtest/gtest.h>

#include "trailblaze/math/interpolation.h"
// related to testing
#include "common.h"

namespace trailblaze {

using test::kLinearInterpolationAccuracy;

TEST(Interpolation, LinearScalarInterpolation)
{
  EXPECT_NEAR(ScalarInterpolator::Linear(0., 1., 0.5), 0.5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(ScalarInterpolator::Linear(1., 2., 0.5), 1.5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(ScalarInterpolator::Linear(0., 10., 0.5), 5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(ScalarInterpolator::Linear(-10., 10., 0.5), 0., kLinearInterpolationAccuracy);
  EXPECT_NEAR(ScalarInterpolator::Linear(0., 1., 0.3), 0.3, kLinearInterpolationAccuracy);
  EXPECT_NEAR(ScalarInterpolator::Linear(0., -1., 0.3), -0.3, kLinearInterpolationAccuracy);
  // this actually extrapolates
  EXPECT_NEAR(ScalarInterpolator::Linear(0., 1., -0.3), -0.3, kLinearInterpolationAccuracy);
}

TEST(Interpolation, LinearAngleInterpolation)
{
  EXPECT_NEAR(InterpolateAngleShortest(ToRad(0.), ToRad(100.), 0.5), ToRad(50),
              kLinearInterpolationAccuracy);
  EXPECT_NEAR(InterpolateAngleShortest(ToRad(1.), ToRad(2.), 0.5), ToRad(1.5),
              kLinearInterpolationAccuracy);
  // angle normalization is to range [-Pi, Pi)
  EXPECT_NEAR(InterpolateAngleShortest(ToRad(0.), ToRad(180.), 0.5), ToRad(-90),
              kLinearInterpolationAccuracy);
  EXPECT_NEAR(InterpolateAngleShortest(ToRad(-179.), ToRad(179.), 0.5), -M_PI,
              kLinearInterpolationAccuracy);
}

}  // namespace trailblaze
