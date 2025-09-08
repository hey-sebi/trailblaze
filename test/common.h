#ifndef TRAILBLAZE_TEST_COMMON_H_
#define TRAILBLAZE_TEST_COMMON_H_

namespace trailblaze {
namespace test {

/// Accuracy that we expect when running linear interpolation on double values
constexpr double kLinearInterpolationAccuracy = 0.000001;

}  // namespace test
}  // namespace trailblaze

#endif