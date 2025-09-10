#include <gtest/gtest.h>

#include "trailblaze/space_r3.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceR3Accessors)
{
  R3 state;
  state.x = 10;
  state.y = 20;
  state.z = 30;
  // read access
  EXPECT_EQ(access::x(state), state.x);
  EXPECT_EQ(access::y(state), state.y);
  EXPECT_EQ(access::z(state), state.z);

  // write access
  access::x(state) = 40;
  access::y(state) = 50;
  access::z(state) = 60;
  EXPECT_EQ(40, state.x);
  EXPECT_EQ(50, state.y);
  EXPECT_EQ(60, state.z);
}

TEST(StateSpaces, SpaceR3Metric)
{
  // Metric in R3 is Euclidean distance.
  typename StateSpace<R3>::Metric dist;

  R3 zero = {0, 0, 0};
  R3 state1;
  state1.x = 1.;
  state1.y = 0.;
  state1.z = 0.;
  EXPECT_DOUBLE_EQ(dist(zero, state1), 1.);

  R3 state2{2., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(state2, state1), 1.);

  R3 state3{5., 4., 3.};
  EXPECT_DOUBLE_EQ(dist(zero, state3), 7.0710678118654752440084436210485);
}

TEST(StateSpaces, SpaceR3LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<R3>::Interp interpolate;
  R3 zero{0., 0., 0.};
  R3 state1{10., 20., 30.};
  R3 result = interpolate(zero, state1, 0.5);
  EXPECT_NEAR(access::x(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(access::y(result), 10., kLinearInterpolationAccuracy);
  EXPECT_NEAR(access::z(result), 15., kLinearInterpolationAccuracy);
}

}  // namespace trailblaze
