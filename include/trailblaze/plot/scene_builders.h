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
typename std::enable_if<trailblaze::has_xy_v<State>, void>::type BuildSceneFromPath(
    const Path<State>& path, Scene* scene)
{
  Polyline2D pl;
  pl.pts.reserve(path.size());
  for (const auto& s : path.states())
  {
    pl.pts.push_back({s.x, s.y});
  }
  scene->polylines.push_back(std::move(pl));
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
  for (std::size_t i = 0; i < path.size(); i += every_n)
  {
    const auto& s = path[i];
    const double c = std::cos(s.yaw);
    const double d = std::sin(s.yaw);
    Arrow2D a;
    a.p = {s.x, s.y};
    a.q = {s.x + arrow_len * c, s.y + arrow_len * d};
    a.head_len = arrow_len * 0.25;
    scene->arrows.push_back(std::move(a));
  }
}

}  // namespace plot
}  // namespace trailblaze

#endif