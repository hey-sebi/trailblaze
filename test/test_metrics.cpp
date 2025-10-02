/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// STL
#include <limits>
// external
#include <gtest/gtest.h>
// this library
#include <trailblaze/metrics/euclidean_distance.h>

namespace trailblaze {

struct TestStateXy
{
  double x;
  double y;
};

template <typename TState>
struct TestParameters
{
  TState in_state1;
  TState in_state2;
  double expected_result;
};

template <typename TMetric, typename TState>
void TestMetric(const std::vector<TestParameters<TState>>& test_params,
                double tolerance = std::numeric_limits<double>::epsilon())
{
  TMetric dist;
  for (const auto& params : test_params)
  {
    double calculated = dist(params.in_state1, params.in_state2);
    EXPECT_NEAR(params.expected_result, calculated, tolerance);
  }
}

TEST(Metric, EuclideanDistance2D)
{
  std::vector<TestParameters<TestStateXy>> test_params = {
      {TestStateXy{0., 0.}, TestStateXy{0., 0.}, 0.},
      {TestStateXy{1., 1.}, TestStateXy{0., 0.}, std::sqrt(2.)}};

  TestMetric<EuclideanDistance2D>(test_params);
}

}  // namespace trailblaze