#include <trailblaze/path.h>
#include <trailblaze/state_spaces/state_space_se2.h>

// for plotting:
#include <trailblaze/plot/matplotlib_renderer.h>
#include <trailblaze/plot/plot_api.h>

int main(int argc, char const* argv[])
{
  using trailblaze::StateSe2;

  trailblaze::Path<StateSe2> p3;
  p3.push_back({0, 0, 0});
  p3.push_back({1, 0.3, 0.2});
  p3.push_back({2, 0.8, 0.4});

  trailblaze::plot::MatplotlibRenderer mpl("plot_path.py");
  trailblaze::plot::PlotSE2Path(p3, mpl);
  return 0;
}