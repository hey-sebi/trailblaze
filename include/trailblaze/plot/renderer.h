/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_PLOT_RENDERER_H_
#define TRAILBLAZE_PLOT_RENDERER_H_

#include <string_view>

#include "trailblaze/plot/scene.h"

namespace trailblaze {
namespace plot {

class renderer {
public:
  virtual ~renderer() = default;

  /** Starts a figure
   *  @param width_px Canvas width in pixel
   *  @param height_px Canvas height in pixel
   */
  virtual void begin_figure(int width_px = 1000, int height_px = 800) = 0;

  /// Ends a figure
  virtual void end_figure() = 0;

  // Drawing
  virtual void draw(const polyline_2d& pl) = 0;
  virtual void draw(const polygon_2d& pg)  = 0;
  virtual void draw(const arrow_2d& ar)    = 0;
  virtual void draw(const text_2d& t)      = 0;

  // View / styling helpers (optional, no-ops by default)
  virtual void set_title(std::string_view title) {}

  virtual void set_axis_equal(bool equal = true) {}

  virtual void set_x_lim(double min_x, double max_x) {}

  virtual void set_y_lim(double min_y, double max_y) {}
};

} // namespace plot
} // namespace trailblaze
#endif