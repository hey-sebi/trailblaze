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
  StateR2 state;
  state.x = 10;
  state.y = 20;

  // read access
  EXPECT_EQ(comp::X(state), state.x);
  EXPECT_EQ(comp::Y(state), state.y);

  // write access
  comp::X(state) = 40;
  comp::Y(state) = 50;
  EXPECT_EQ(40, state.x);
  EXPECT_EQ(50, state.y);
}

TEST(StateSpaces, SpaceR2Metric) {
  // Metric in R2 is Euclidean distance.
  typename StateSpace<StateR2>::Metric dist;

  StateR2 zero = {0, 0};
  StateR2 state;
  state.x = 1;
  state.y = 0;
  EXPECT_DOUBLE_EQ(dist(zero, state), 1.);

  state.x = -3;
  state.y = 4;
  EXPECT_DOUBLE_EQ(dist(zero, state), 5.);
}

TEST(StateSpaces, SpaceR2LinearInterpolation) {
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<StateR2>::Interpolation Interpolator;
  StateR2                                     zero{0., 0.};
  StateR2                                     state1{10., 20.};
  StateR2                                     result = Interpolator(zero, state1, 0.5);
  EXPECT_NEAR(comp::X(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::Y(result), 10., kLinearInterpolationAccuracy);
}

} // namespace trailblaze
