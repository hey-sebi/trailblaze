/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <iterator>
#include <vector>

#include "trailblaze/algorithm/resample.h"
#include "trailblaze/path.h"
#include "trailblaze/state_spaces/state_space_se2.h"

void run_example() {
  trailblaze::path<trailblaze::state_se2> path;
  // ... fill the path ...
  path.reserve(5);
  path.push_back({0., 0., 0.});
  path.push_back({1., 0., 0.});
  path.push_back({2., 0., 0.});
  path.push_back({3., 0., 0.});
  path.push_back({4., 0., 0.});

  std::vector<trailblaze::state_se2> out;
  out.reserve(path.size() * 2);
  auto insert_it = std::back_inserter(out);
  const double sample_density = 0.1;
  trailblaze::resample(path.states(), sample_density, insert_it);
}

int main(int argc, char const* argv[]) {
  run_example();
  return 0;
}
