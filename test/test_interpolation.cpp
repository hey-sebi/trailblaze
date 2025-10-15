/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// external
#include <gtest/gtest.h>

#include "trailblaze/backport/numbers.h"
#include "trailblaze/math/interpolation.h"
// related to testing
#include "common.h"

namespace trailblaze {

using test::kLinearInterpolationAccuracy;

TEST(Interpolation, LinearScalarInterpolation) {
  EXPECT_NEAR(scalar_interpolator::linear(0., 1., 0.5), 0.5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(scalar_interpolator::linear(1., 2., 0.5), 1.5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(scalar_interpolator::linear(0., 10., 0.5), 5, kLinearInterpolationAccuracy);
  EXPECT_NEAR(scalar_interpolator::linear(-10., 10., 0.5), 0., kLinearInterpolationAccuracy);
  EXPECT_NEAR(scalar_interpolator::linear(0., 1., 0.3), 0.3, kLinearInterpolationAccuracy);
  EXPECT_NEAR(scalar_interpolator::linear(0., -1., 0.3), -0.3, kLinearInterpolationAccuracy);
  // this actually extrapolates
  EXPECT_NEAR(scalar_interpolator::linear(0., 1., -0.3), -0.3, kLinearInterpolationAccuracy);
}

TEST(Interpolation, LinearAngleInterpolation) {
  EXPECT_NEAR(interpolate_angle_shortest(to_rad(0.), to_rad(100.), 0.5), to_rad(50),
              kLinearInterpolationAccuracy);
  EXPECT_NEAR(interpolate_angle_shortest(to_rad(1.), to_rad(2.), 0.5), to_rad(1.5),
              kLinearInterpolationAccuracy);
  // angle normalization is to range [-Pi, Pi)
  EXPECT_NEAR(interpolate_angle_shortest(to_rad(0.), to_rad(180.), 0.5), to_rad(-90),
              kLinearInterpolationAccuracy);
  EXPECT_NEAR(interpolate_angle_shortest(to_rad(-179.), to_rad(179.), 0.5), -numbers::pi,
              kLinearInterpolationAccuracy);
}

} // namespace trailblaze
