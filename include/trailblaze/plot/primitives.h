/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_PLOT_PRIMITIVES_H_
#define TRAILBLAZE_PLOT_PRIMITIVES_H_
#include <array>
#include <string>
#include <vector>

namespace trailblaze {
namespace plot {

/// Sequence of lines connecting 2-dim points
struct Polyline2D
{
  std::vector<std::array<double, 2>> pts;
};

/// Collection of points that form a polygon.
struct Polygon2D
{
  std::vector<std::array<double, 2>> pts;
};

struct Arrow2D
{
  std::array<double, 2> p, q;
  double head_len{0.1};
};

struct Text2D
{
  std::array<double, 2> p;
  std::string text;
  double size{10.0};
};

}  // namespace plot
}  // namespace trailblaze

#endif