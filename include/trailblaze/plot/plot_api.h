/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_PLOT_PLOT_API_H_
#define TRAILBLAZE_PLOT_PLOT_API_H_

#include "trailblaze/path.h"
#include "trailblaze/state_traits.h"
// plotting related
#include "trailblaze/plot/primitives.h"
#include "trailblaze/plot/renderer.h"
#include "trailblaze/plot/scene_builders.h"

namespace trailblaze {
namespace plot {

inline void RenderScene(const Scene& sc,
                        Renderer&    r,
                        int          width_px  = 1000,
                        int          height_px = 800,
                        std::string  title     = {}) {
  r.BeginFigure(width_px, height_px);
  if (!title.empty()) {
    r.SetTitle(title);
  }
  r.SetAxisEqual(true);
  for (const auto& pl : sc.polylines)
    r.Draw(pl);
  for (const auto& pg : sc.polygons)
    r.Draw(pg);
  for (const auto& ar : sc.arrows)
    r.Draw(ar);
  for (const auto& tx : sc.texts)
    r.Draw(tx);
  r.EndFigure();
}

template <typename State>
inline void
PlotR2Path(const trailblaze::Path<State>& path, Renderer& r, std::string title = "Path (R^2)") {
  static_assert(trailblaze::has_xy_v<State>, "PlotR2Path requires a state with members x and y.");
  Scene sc;
  BuildSceneFromPath(path, &sc);
  RenderScene(sc, r, 1000, 800, std::move(title));
}

template <typename State>
inline void
PlotSE2Path(const trailblaze::Path<State>& path, Renderer& r, std::string title = "Path (SE(2))") {
  static_assert(trailblaze::has_xy_v<State> && trailblaze::has_yaw_v<State>,
                "PlotSE2Path requires a state with x, y, yaw.");
  Scene sc;
  BuildSceneFromPathSE2(path, &sc);
  RenderScene(sc, r, 1000, 800, std::move(title));
}

} // namespace plot
} // namespace trailblaze

#endif