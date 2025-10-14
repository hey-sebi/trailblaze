/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include "trailblaze/path.h"
#include "trailblaze/state_spaces/state_space_se2.h"

// for plotting:
#include "trailblaze/plot/matplotlib_renderer.h"
#include "trailblaze/plot/plot_api.h"

int main(int argc, char const* argv[]) {
  using trailblaze::state_se2;

  trailblaze::Path<state_se2> p3;
  p3.push_back({0, 0, 0});
  p3.push_back({1, 0.3, 0.2});
  p3.push_back({2, 0.8, 0.4});

  trailblaze::plot::MatplotlibRenderer mpl("plot_path.py");
  trailblaze::plot::plot_se2_path(p3, mpl);
  return 0;
}