/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <string_view>

#include "trailblaze/interval.h"
#include "trailblaze/plot/scene.h"
#include "trailblaze/plot/scene_options.h"

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
   *  @param dim Canvas dimensions in pixels
   */
  virtual void begin_figure(const canvas_dimension& dim = canvas_dimension(1000, 800)) = 0;

  /// Ends a figure
  virtual void end_figure() = 0;

  /* --------------------------------------------------------------
   *  Drawing of primitives
   * -------------------------------------------------------------- */

  /** Draws a polyline on the canvas.
   *  @param polyline The polyline to draw.
   */
  virtual void draw(const polyline_2d& polyline) = 0;

  /** Draws a polygon on the canvas.
   *  @param polygon The polygon to draw.
   */
  virtual void draw(const polygon_2d& polygon) = 0;

  /** Draws a arrow on the canvas.
   *  @param arrow The arrow to draw.
   */
  virtual void draw(const arrow_2d& arrow) = 0;

  /** Draws a arrow on the canvas.
   *  @param arrow The arrow to draw.
   */
  virtual void draw(const text_2d& text) = 0;

  /* --------------------------------------------------------------
   *  View / styling helpers
   * -------------------------------------------------------------- */

  /** Set the plot title.
   *
   *  The title is optional, all backends have to check if the title is an empty string
   *  and in this case omit title plotting, including related formatting commands.
   */
  virtual void set_title(std::string_view title) {}

  /** Allows setting the aspect ratio of the axes so that one unit in the y-data
   *  coordinates is scaled to be the same size as one unit in the x-data coordinates,
   *  ensuring that shapes like circles appear undistorted.
   *
   *  @param equal Enables fix aspect ratio if @c true.
   */
  virtual void set_axis_equal(bool equal = true) {}

  virtual void set_x_lim(const interval<double>& x_range) {}

  virtual void set_y_lim(const interval<double>& y_range) {}
};

} // namespace trailblaze::plot