/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include "trailblaze/path.h"
#include "trailblaze/state_traits.h"
// plotting related
#include "trailblaze/plot/primitives.h"
#include "trailblaze/plot/renderer.h"
#include "trailblaze/plot/scene_builders.h"
#include "trailblaze/plot/scene_options.h"

namespace trailblaze::plot {

/** Renders a scene using a certain renderer.
 *
 *  @param to_plot The scene to render.
 *  @param renderer_backend The backend to use (e.g. Matplotlib, GnuPlot, ...).
 *  @param dim The canvas dimensions.
 *  @param title The optional title. Only considered if not an empty string.
 */
inline void render_scene(const scene& to_plot, renderer& renderer_backend,
                         canvas_dimension dim = canvas_dimension(1000, 800),
                         std::string_view title = {}) {
  renderer_backend.begin_figure(dim);
  if (!title.empty()) {
    renderer_backend.set_title(title);
  }
  renderer_backend.set_axis_equal(true);
  for (const auto& polyline : to_plot.polylines) {
    renderer_backend.draw(polyline);
  }
  for (const auto& polygon : to_plot.polygons) {
    renderer_backend.draw(polygon);
  }
  for (const auto& arrow : to_plot.arrows) {
    renderer_backend.draw(arrow);
  }
  for (const auto& text : to_plot.texts) {
    renderer_backend.draw(text);
  }
  renderer_backend.end_figure();
}

template <typename TState>
inline void plot_r2_path(const trailblaze::path<TState>& path, renderer& renderer_backend,
                         std::string_view title = "Path (R^2)") {
  static_assert(trailblaze::has_xy_v<TState>,
                "plot_r2_path requires a state with members x and y.");
  scene scene_with_path;
  build_scene_from_path(path, scene_with_path);
  render_scene(scene_with_path, renderer_backend, canvas_dimension(1000, 800), title);
}

template <typename TState>
inline void plot_se2_path(const trailblaze::path<TState>& path, renderer& renderer_backend,
                          std::string_view title = "Path (SE(2))") {
  static_assert(trailblaze::has_xy_v<TState> && trailblaze::has_yaw_v<TState>,
                "plot_se2_path requires a state with x, y, yaw.");
  scene scene_with_path;
  build_scene_from_path_se2(path, scene_with_path);
  render_scene(scene_with_path, renderer_backend, canvas_dimension(1000, 800), title);
}

} // namespace trailblaze::plot
