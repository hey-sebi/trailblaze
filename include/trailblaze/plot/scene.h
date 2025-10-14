/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_PLOT_SCENE_H_
#define TRAILBLAZE_PLOT_SCENE_H_

#include "trailblaze/plot/primitives.h"

namespace trailblaze {
namespace plot {

struct scene {
  std::vector<polyline_2d> polylines;
  std::vector<polygon_2d>  polygons;
  std::vector<arrow_2d>    arrows;
  std::vector<text_2d>     texts;
  // Optional: view box, styles, layers, palette, grid, etc.
};

} // namespace plot
} // namespace trailblaze

#endif