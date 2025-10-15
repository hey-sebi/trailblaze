/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <iostream>

#include "trailblaze/generate.h"
#include "trailblaze/path.h"
#include "trailblaze/sampling.h"
#include "trailblaze/state_spaces/state_space_r2.h"

int main(int argc, char const* argv[]) {
  using trailblaze::path;
  using trailblaze::state_r2;

  state_r2 start{1.0, 1.0};
  state_r2 goal{10.0, 8.0};
  trailblaze::sampling::by_count policy;
  policy.n = 100;
  path<state_r2> path_r2 = trailblaze::gen::line_r2(start, goal, policy);

  std::cout << "Path state_r2 with " << path_r2.size() << " states:\n" << path_r2;
  return 0;
}
