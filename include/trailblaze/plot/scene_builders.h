#ifndef TRAILBLAZE_PLOT_SCENE_BUILDERS_H_
#define TRAILBLAZE_PLOT_SCENE_BUILDERS_H_

// STL
#include <cmath>

#include "trailblaze/path.h"
#include "trailblaze/traits.h"
// plotting related
#include "trailblaze/plot/scene.h"

namespace trailblaze {
namespace plot {

// ----- R^2: requires x,y -----------------------------------------------------

template <typename State>
typename std::enable_if<trailblaze::has_xy_v<State>, void>::type

BuildSceneFromPath(const Path<State>& path, Scene* scene, double arrow_len = 0.25,
                   std::size_t every_n = 10)
{
  Polyline2D polyline;
  polyline.pts.reserve(path.size());
  if (every_n == 0)
  {
    every_n = 1;
  }
  if (path.size() < every_n)
  {
    every_n = 1;
  }
  for (std::size_t i = 0; i < path.size(); i += every_n)
  {
    const auto& state = path[i];
    polyline.pts.push_back({state.x, state.y});
    scene->polylines.push_back(std::move(polyline));
  }
}

// ----- SE(2): requires x,y,yaw  ----------------------------------------------

template <typename State>
typename std::enable_if<trailblaze::has_xy_v<State> && trailblaze::has_yaw_v<State>,
                        void>::type
BuildSceneFromPathSE2(const trailblaze::Path<State>& path, Scene* scene,
                      double arrow_len = 0.25, std::size_t every_n = 10)
{
  // reuse the R^2 polyline
  BuildSceneFromPath(path, scene);

  if (every_n == 0)
  {
    every_n = 1;
  }
  if (path.size() < every_n)
  {
    every_n = 1;
  }
  for (std::size_t i = 0; i < path.size(); i += every_n)
  {
    const auto& state = path[i];
    const double cos = std::cos(state.yaw);
    const double sin = std::sin(state.yaw);
    Arrow2D arrow;
    arrow.p = {state.x, state.y};
    arrow.q = {state.x + arrow_len * cos, state.y + arrow_len * sin};
    arrow.head_len = arrow_len * 0.25;
    scene->arrows.push_back(std::move(arrow));
  }
}

}  // namespace plot
}  // namespace trailblaze

#endif