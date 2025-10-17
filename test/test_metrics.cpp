/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// STL
#include <cmath>
#include <limits>
#include <vector>
// external
#include <gtest/gtest.h>
// this library
#include "trailblaze/metrics/euclidean_distance.h"

namespace trailblaze {

struct test_state_xy {
  double x{0.};
  double y{0.};
};

template <typename TState>
struct test_parameters {
  TState in_state1;
  TState in_state2;
  double expected_result{0.};
};

template <typename TMetric, typename TState>
void test_metric(const std::vector<test_parameters<TState>>& test_params,
                 double tolerance = std::numeric_limits<double>::epsilon()) {
  TMetric dist;
  for (const auto& params : test_params) {
    double calculated = dist(params.in_state1, params.in_state2);
    EXPECT_NEAR(params.expected_result, calculated, tolerance);
  }
}

TEST(Metric, EuclideanDistance2d) {
  std::vector<test_parameters<test_state_xy>> test_params = {
      {test_state_xy{0., 0.}, test_state_xy{0., 0.}, 0.},
      {test_state_xy{1., 1.}, test_state_xy{0., 0.}, std::sqrt(2.)}};

  test_metric<euclidean_distance_2d>(test_params);
}

} // namespace trailblaze