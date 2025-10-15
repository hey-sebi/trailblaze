/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <string_view>

#include "trailblaze/interval.h"
#include "trailblaze/plot/scene.h"

namespace trailblaze::plot {

class renderer {
public:
  renderer() = default;
  renderer(const renderer& other) = default;
  renderer(renderer&& other) = default;
  virtual ~renderer() = default;
  renderer& operator=(const renderer& other) = default;
  renderer& operator=(renderer&& other) = default;

  /** Starts a figure
   *  @param width_px Canvas width in pixel
   *  @param height_px Canvas height in pixel
   */
  virtual void begin_figure(int width_px = 1000, int height_px = 800) = 0;

  /// Ends a figure
  virtual void end_figure() = 0;

  // Drawing
  virtual void draw(const polyline_2d& pl) = 0;
  virtual void draw(const polygon_2d& pg) = 0;
  virtual void draw(const arrow_2d& ar) = 0;
  virtual void draw(const text_2d& t) = 0;

  // View / styling helpers (optional, no-ops by default)
  virtual void set_title(std::string_view title) {}

  virtual void set_axis_equal(bool equal = true) {}

  virtual void set_x_lim(const interval<double>& x_range) {}

  virtual void set_y_lim(const interval<double>& y_range) {}
};

} // namespace trailblaze::plot