#include <gtest/gtest.h>

#include "trailblaze/math/angle.h"

namespace trailblaze {

TEST(TestAngle, TestDegToRadConversion)
{
  EXPECT_DOUBLE_EQ(ToRad(0.), 0);
  EXPECT_DOUBLE_EQ(ToRad(90.), M_PI_2);
  EXPECT_DOUBLE_EQ(ToRad(-90.), -M_PI_2);
  EXPECT_DOUBLE_EQ(ToRad(180.), M_PI);
}

TEST(TestAngle, TestAngleNormalization)
{
  EXPECT_DOUBLE_EQ(NormalizeAngle(M_PI), -M_PI);
  EXPECT_DOUBLE_EQ(NormalizeAngle(-M_PI), -M_PI);
}

}  // namespace trailblaze
