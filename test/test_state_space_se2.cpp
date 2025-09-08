#include <gtest/gtest.h>

#include "trailblaze/space_se2.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(TestStateSpaces, TestSpaceSE2Accessors)
{
  SE2 state;
  state.x = 10;
  state.y = 20;
  state.yaw = 0.1234;
  // read access
  EXPECT_EQ(access::x(state), state.x);
  EXPECT_EQ(access::y(state), state.y);
  EXPECT_EQ(access::yaw(state), state.yaw);

  // write access
  access::x(state) = 40;
  access::y(state) = 50;
  access::yaw(state) = 1.;
  EXPECT_EQ(40., state.x);
  EXPECT_EQ(50., state.y);
  EXPECT_EQ(1., state.yaw);
}

TEST(TestStateSpaces, TestSpaceSE2Metric)
{
  // Metric in SE2 is Euclidean distance on R2
  typename StateSpace<SE2>::Metric dist;

  SE2 zero = {0., 0., 0.};

  SE2 state1 = {1., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(zero, state1), 1.);

  SE2 state2{2., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(state2, state1), 1.);

  SE2 state3{3., 4., 0.12};
  EXPECT_DOUBLE_EQ(dist(zero, state3), 5.);
}

TEST(TestStateSpaces, TestSpaceSE2LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<SE2>::Interp interpolate;
  SE2 zero{0., 0., 0.};
  SE2 state1{10., 20., 1.};
  SE2 result = interpolate(zero, state1, 0.5);
  EXPECT_NEAR(access::x(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(access::y(result), 10., kLinearInterpolationAccuracy);
  EXPECT_NEAR(access::yaw(result), .5, kLinearInterpolationAccuracy);
}

}  // namespace trailblaze
