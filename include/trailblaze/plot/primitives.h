/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <array>
#include <string>
#include <vector>

namespace trailblaze::plot {

/// Sequence of lines connecting 2-dim points
struct polyline_2d {
  std::vector<std::array<double, 2>> pts;
};

/// Collection of points that form a polygon.
struct polygon_2d {
  std::vector<std::array<double, 2>> pts;
};

struct arrow_2d {
  std::array<double, 2> p, q;
  double head_len{0.1};
};

struct text_2d {
  std::array<double, 2> p;
  std::string_view text;
  double size{10.0};
};

} // namespace trailblaze::plot
