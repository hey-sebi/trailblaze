
# trailblaze

![trailblaze logo](/docs/images/trailblaze_logo.png)

> A C++ library for modeling and analyzing paths (SE(2) and beyond) for robotics.

## Getting started

- **Headers:** `#include <trailblaze/...>`
- **Docs build:** `cmake --build build --target doc` → open `build/docs/html/index.html`.












## Generating plots

Trailblaze has support for generating plots for different backends, e.g. MatplotLib, GnuPlot or SVGs. It can also be easily extended to support other formats.

Example on how to generate plots for Matplotlib:
```C++
#include <trailblaze/path.h>
#include <trailblaze/space_se2.h>

// for plotting:
#include <trailblaze/plot/matplotlib_renderer.h>
#include <trailblaze/plot/plot_api.h>

int main(int argc, char const* argv[])
{
  using trailblaze::SE2;

  trailblaze::Path<SE2> p3;
  p3.push_back({0, 0, 0});
  p3.push_back({1, 0.3, 0.2});
  p3.push_back({2, 0.8, 0.4});

  trailblaze::plot::MatplotlibRenderer mpl("plot_path.py");
  trailblaze::plot::PlotSE2Path(p3, mpl);
  return 0;
}
```
