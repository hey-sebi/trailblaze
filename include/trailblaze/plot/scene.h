#ifndef TRAILBLAZE_PLOT_SCENE_H_
#define TRAILBLAZE_PLOT_SCENE_H_

#include "trailblaze/plot/primitives.h"

namespace trailblaze {
namespace plot {

struct Scene
{
  std::vector<Polyline2D> polylines;
  std::vector<Polygon2D> polygons;
  std::vector<Arrow2D> arrows;
  std::vector<Text2D> texts;
  // Optional: view box, styles, layers, palette, grid, etc.
};

}  // namespace plot
}  // namespace trailblaze

#endif