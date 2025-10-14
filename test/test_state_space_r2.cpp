/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <gtest/gtest.h>

#include "trailblaze/state_spaces/state_space_r2.h"
// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceR2Accessors) {
  state_r2 state;
  state.x = 10;
  state.y = 20;

  // read access
  EXPECT_EQ(comp::x(state), state.x);
  EXPECT_EQ(comp::y(state), state.y);

  // write access
  comp::x(state) = 40;
  comp::y(state) = 50;
  EXPECT_EQ(40, state.x);
  EXPECT_EQ(50, state.y);
}

TEST(StateSpaces, SpaceR2Metric) {
  // Metric in R2 is Euclidean distance.
  typename state_space<state_r2>::metric_type dist;

  state_r2 zero = {0, 0};
  state_r2 state;
  state.x = 1;
  state.y = 0;
  EXPECT_DOUBLE_EQ(dist(zero, state), 1.);

  state.x = -3;
  state.y = 4;
  EXPECT_DOUBLE_EQ(dist(zero, state), 5.);
}

TEST(StateSpaces, SpaceR2LinearInterpolation) {
  using test::kLinearInterpolationAccuracy;
  typename state_space<state_r2>::interpolation_type Interpolator;

  state_r2 zero{0., 0.};
  state_r2 state1{10., 20.};
  state_r2 result = Interpolator(zero, state1, 0.5);
  EXPECT_NEAR(comp::x(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::y(result), 10., kLinearInterpolationAccuracy);
}

} // namespace trailblaze
