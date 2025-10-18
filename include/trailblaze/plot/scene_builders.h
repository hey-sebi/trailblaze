/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
// STL
#include <cmath>

#include "trailblaze/path.h"
#include "trailblaze/state_traits.h"
// plotting related
#include "trailblaze/plot/scene.h"
#include "trailblaze/plot/scene_options.h"

namespace trailblaze::plot {

/** Builds a scene containing information from a path.
 *  @tparam TState The state type which must satisfy the predicate @e has_xy_v.
 *  @param path The path to plot
 *  @param scene The scene to append data to.
 *  @param arrow_len (Reserved for future use; currently unused.)
 *  @param stride The sample stride. Only takes every n samples from the path into the
 *         scene. Values < 1 are treated as 1.
 */
template <typename TState>
typename std::enable_if_t<trailblaze::has_xy_v<TState>, void>
build_scene_from_path(const path<TState>& path, scene& scene,
                      arrow_length arrow_len = arrow_length(0.25),
                      sample_stride stride = sample_stride(10)) {
  polyline_2d polyline;
  polyline.pts.reserve(path.size());
  // Use all samples in case there are too few.
  if (path.size() < stride.value) {
    stride.value = 1;
  }
  for (std::size_t i = 0; i < path.size(); i += stride.value) {
    const auto& state = path[i];
    polyline.pts.push_back({state.x, state.y});
  }
  scene.polylines.push_back(std::move(polyline));
}

/** Builds a scene containing information from a path.
 *  @tparam TState The state type which must satisfy the predicates @e has_xy_v
 *          and @e has_yaw_v.
 *  @param path The path to plot
 *  @param scene The scene to append data to.
 *  @param arrow_len Length of arrows used to indicate the orientation (from yaw values).
 *  @param every_n The sample stride. Only takes every n samples from the path into the
 *         scene. Values < 1 are treated as 1.
 */
template <typename TState>
typename std::enable_if_t<trailblaze::has_xy_v<TState> && trailblaze::has_yaw_v<TState>, void>
build_scene_from_path_se2(const trailblaze::path<TState>& path, scene& scene,
                          arrow_length arrow_len = arrow_length(0.25),
                          sample_stride stride = sample_stride(10)) {
  // Use all samples in case there are too few.
  if (path.size() < stride.value) {
    stride.value = 1;
  }
  // for x & y values
  build_scene_from_path(path, scene, arrow_len, stride);
  // for yaw values
  for (std::size_t i = 0; i < path.size(); i += stride.value) {
    const auto& state = path[i];
    const double cos = std::cos(state.yaw);
    const double sin = std::sin(state.yaw);
    arrow_2d arrow;
    arrow.p = {state.x, state.y};
    arrow.q = {state.x + arrow_len.value * cos, state.y + arrow_len.value * sin};
    arrow.head_length = arrow_len.value * 0.25;
    scene.arrows.push_back(arrow);
  }
}

} // namespace trailblaze::plot
