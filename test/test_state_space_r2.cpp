#include <gtest/gtest.h>

#include "trailblaze/space_r2.h"
// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceR2Accessors)
{
  R2 state;
  state.x = 10;
  state.y = 20;
  // read access
  EXPECT_EQ(access::x(state), state.x);
  EXPECT_EQ(access::y(state), state.y);

  // write access
  access::x(state) = 40;
  access::y(state) = 50;
  EXPECT_EQ(40, state.x);
  EXPECT_EQ(50, state.y);
}

TEST(StateSpaces, SpaceR2Metric)
{
  // Metric in R2 is Euclidean distance.
  typename StateSpace<R2>::Metric dist;

  R2 zero = {0, 0};
  R2 state;
  state.x = 1;
  state.y = 0;
  EXPECT_DOUBLE_EQ(dist(zero, state), 1.);

  state.x = -3;
  state.y = 4;
  EXPECT_DOUBLE_EQ(dist(zero, state), 5.);
}

TEST(StateSpaces, SpaceR2LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<R2>::Interp interpolate;
  R2 zero{0., 0.};
  R2 state1{10., 20.};
  R2 result = interpolate(zero, state1, 0.5);
  EXPECT_NEAR(access::x(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(access::y(result), 10., kLinearInterpolationAccuracy);
}

}  // namespace trailblaze
