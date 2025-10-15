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
  state_se2 state;
  state.x = 10;
  state.y = 20;
  state.yaw = 0.1234;

  // read access
  EXPECT_EQ(comp::x(state), state.x);
  EXPECT_EQ(comp::y(state), state.y);
  EXPECT_EQ(comp::yaw(state), state.yaw);

  // write access
  comp::x(state) = 40;
  comp::y(state) = 50;
  comp::yaw(state) = 1.;
  EXPECT_EQ(40., state.x);
  EXPECT_EQ(50., state.y);
  EXPECT_EQ(1., state.yaw);
}

TEST(StateSpaces, SpaceSE2Metric) {
  typename state_space<state_se2>::metric_type dist;

  state_se2 zero = {0., 0., 0.};

  state_se2 state1 = {1., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(zero, state1), 1.);

  state_se2 state2{2., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(state2, state1), 1.);

  state_se2 state3{3., 4., 0.12};
  EXPECT_DOUBLE_EQ(dist(zero, state3), 5.);
}

TEST(StateSpaces, SpaceSE2LinearInterpolation) {
  using test::linear_interpolation_accuracy;
  typename state_space<state_se2>::interpolation_type interpolation;

  state_se2 zero{0., 0., 0.};
  state_se2 state1{10., 20., 1.};
  state_se2 result = interpolation(zero, state1, 0.5);
  EXPECT_NEAR(comp::x(result), 5., linear_interpolation_accuracy);
  EXPECT_NEAR(comp::y(result), 10., linear_interpolation_accuracy);
  EXPECT_NEAR(comp::yaw(result), .5, linear_interpolation_accuracy);
}

} // namespace trailblaze
