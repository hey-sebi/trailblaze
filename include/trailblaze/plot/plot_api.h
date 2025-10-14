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

inline void render_scene(const scene& sc,
                         renderer&    r,
                         int          width_px  = 1000,
                         int          height_px = 800,
                         std::string  title     = {}) {
  r.begin_figure(width_px, height_px);
  if (!title.empty()) {
    r.set_title(title);
  }
  r.set_axis_equal(true);
  for (const auto& pl : sc.polylines)
    r.draw(pl);
  for (const auto& pg : sc.polygons)
    r.draw(pg);
  for (const auto& ar : sc.arrows)
    r.draw(ar);
  for (const auto& tx : sc.texts)
    r.draw(tx);
  r.end_figure();
}

template <typename TState>
inline void
plot_r2_path(const trailblaze::path<TState>& path, renderer& r, std::string title = "Path (R^2)") {
  static_assert(trailblaze::has_xy_v<TState>, "plot_r2_path requires a state with members x and y.");
  scene sc;
  build_scene_from_path(path, &sc);
  render_scene(sc, r, 1000, 800, std::move(title));
}

template <typename TState>
inline void plot_se2_path(const trailblaze::path<TState>& path,
                          renderer&                      r,
                          std::string                    title = "Path (SE(2))") {
  static_assert(trailblaze::has_xy_v<TState> && trailblaze::has_yaw_v<TState>,
                "plot_se2_path requires a state with x, y, yaw.");
  scene sc;
  build_scene_from_path_se2(path, &sc);
  render_scene(sc, r, 1000, 800, std::move(title));
}

} // namespace plot
} // namespace trailblaze

#endif