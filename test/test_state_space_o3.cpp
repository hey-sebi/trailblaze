#include <gtest/gtest.h>

#include "trailblaze/component_access.h"
#include "trailblaze/state_spaces/state_space_o3.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(StateSpaces, SpaceO3Accessors)
{
  StateO3 state;
  state.orientation.x = 0;
  state.orientation.y = 0;
  state.orientation.z = 0;
  state.orientation.w = 1;

  // read access
  EXPECT_EQ(comp::Qx(state), state.orientation.x);
  EXPECT_EQ(comp::Qy(state), state.orientation.y);
  EXPECT_EQ(comp::Qz(state), state.orientation.z);
  EXPECT_EQ(comp::Qw(state), state.orientation.w);

  // write access
  comp::Qx(state) = 0.1;
  comp::Qy(state) = 0.2;
  comp::Qz(state) = 0.3;
  comp::Qw(state) = 0.4;
  EXPECT_EQ(0.1, state.orientation.x);
  EXPECT_EQ(0.2, state.orientation.y);
  EXPECT_EQ(0.3, state.orientation.z);
  EXPECT_EQ(0.4, state.orientation.w);
}

TEST(StateSpaces, SpaceO3LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<StateO3>::Interpolation interpolate;
  // TODO
}

}  // namespace trailblaze
