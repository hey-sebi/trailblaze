#include <gtest/gtest.h>

#include "trailblaze/component_access.h"
#include "trailblaze/state_spaces/state_space_r3.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceR3Accessors)
{
  StateR3 state;
  state.x = 10;
  state.y = 20;
  state.z = 30;

  // read access
  EXPECT_EQ(comp::X(state), state.x);
  EXPECT_EQ(comp::Y(state), state.y);
  EXPECT_EQ(comp::Z(state), state.z);

  // write access
  comp::X(state) = 40;
  comp::Y(state) = 50;
  comp::Z(state) = 60;
  EXPECT_EQ(40, state.x);
  EXPECT_EQ(50, state.y);
  EXPECT_EQ(60, state.z);
}

TEST(StateSpaces, SpaceR3Metric)
{
  // Metric in R3 is Euclidean distance.
  typename StateSpace<StateR3>::Metric dist;

  StateR3 zero = {0, 0, 0};
  StateR3 state1;
  state1.x = 1.;
  state1.y = 0.;
  state1.z = 0.;
  EXPECT_DOUBLE_EQ(dist(zero, state1), 1.);

  StateR3 state2{2., 0., 0.};
  EXPECT_DOUBLE_EQ(dist(state2, state1), 1.);

  StateR3 state3{5., 4., 3.};
  EXPECT_DOUBLE_EQ(dist(zero, state3), 7.0710678118654752440084436210485);
}

TEST(StateSpaces, SpaceR3LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<StateR3>::Interpolation Interpolator;
  StateR3 zero{0., 0., 0.};
  StateR3 state1{10., 20., 30.};
  StateR3 result = Interpolator(zero, state1, 0.5);
  EXPECT_NEAR(comp::X(result), 5., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::Y(result), 10., kLinearInterpolationAccuracy);
  EXPECT_NEAR(comp::Z(result), 15., kLinearInterpolationAccuracy);
}

}  // namespace trailblaze
