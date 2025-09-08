
#include <gtest/gtest.h>

#include "trailblaze/space_o3.h"

// related to testing
#include "common.h"

namespace trailblaze {

TEST(TestStateSpaces, TestSpaceO3Accessors)
{
  O3 state;
  state.orientation.x = 0;
  state.orientation.y = 0;
  state.orientation.z = 0;
  state.orientation.w = 1;
  // read access
  EXPECT_EQ(access::qx(state), state.orientation.x);
  EXPECT_EQ(access::qy(state), state.orientation.y);
  EXPECT_EQ(access::qz(state), state.orientation.z);
  EXPECT_EQ(access::qw(state), state.orientation.w);

  // write access
  access::qx(state) = 0.1;
  access::qy(state) = 0.2;
  access::qz(state) = 0.3;
  access::qw(state) = 0.4;
  EXPECT_EQ(0.1, state.orientation.x);
  EXPECT_EQ(0.2, state.orientation.y);
  EXPECT_EQ(0.3, state.orientation.z);
  EXPECT_EQ(0.4, state.orientation.w);
}

TEST(TestStateSpaces, TestSpaceO3LinearInterpolation)
{
  using test::kLinearInterpolationAccuracy;
  typename StateSpace<O3>::Interp interpolate;
  // TODO
}

}  // namespace trailblaze
