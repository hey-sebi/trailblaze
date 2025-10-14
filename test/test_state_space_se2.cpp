/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <gtest/gtest.h>

#include "trailblaze/component_access.h"
#include "trailblaze/state_spaces/state_space_se2.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceSE2Accessors) {
  StateSe2 state;
  state.x   = 10;
  state.y   = 20;
  state.yaw = 0.1234;

  // read access
  EXPECT_EQ(comp::X(state), state.x);
  EXPECT_EQ(comp::Y(state), state.y);
  EXPECT_EQ(comp::Yaw(state), state.yaw);

  // write access
  comp::X(state)   = 40;
  comp::Y(state)   = 50;
  comp::Yaw(state) = 1.;
  EXPECT_EQ(40., state.x);
  EXPECT_EQ(50., state.y);
  EXPECT_EQ(1., state.yaw);
}

TEST(StateSpaces, SpaceSE2Metric) {
  typename StateSpace<StateSe2>::Metric dist;

  StateSe2 zero = {0., 0., 0.};

  StateSe2 state1 = {1., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(zero, state1), 1.);

  StateSe2 state2{2., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(state2, state1), 1.);

  StateSe2 state3{3., 4., 0.12};
  EXPECT_DOUBLE_EQ(dist(zero, state3), 5.);
}

TEST(StateSpaces, SpaceSE2LinearInterpolation) {
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<StateSe2>::Interpolation Interpolator;
  StateSe2                                     zero{0., 0., 0.};
  StateSe2                                     state1{10., 20., 1.};
  StateSe2                                     result = Interpolator(zero, state1, 0.5);
  EXPECT_NEAR(comp::X(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::Y(result), 10., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::Yaw(result), .5, kLinearInterpolationAccuracy);
}

} // namespace trailblaze
