/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <algorithm>
#include <cstddef>

namespace trailblaze::plot {

/** Type-safe wrapper representing an arrow length parameter.
 *
 *  Used to specify the visual length of arrows when rendering scenes.
 *  This type prevents confusion with other floating-point parameters.
 */
struct arrow_length {
  /** Constructs an arrow length with the given value.
   *  @param length Length of the arrow (in scene units).
   */
  explicit arrow_length(double length) : value(length) {}
  /// The arrow's length (in scene units).
  double value{1.};
};

/** Type-safe wrapper representing the sampling stride for scene generation.
 *
 *  Determines how densely the input path is sampled when constructing a scene.
 *  A larger stride reduces the number of samples considered.
 */
struct sample_stride {
  /** Constructs a sampling stride with the given length.
   *  @param stride_length A value >= 1 specifying the sampling interval.
   */
  explicit sample_stride(std::size_t stride_length)
      : value(std::max(stride_length, std::size_t{1})) {}

  /** Sampling interval between path elements.
   *
   *  A value of 1 means every element in the input path is used.
   *  A value of 10 means only every 10th element is considered.
   */
  std::size_t value{1};
};

/// Type-safe wrapper representing the dimensions for the canvas a scene is drawn to.
struct canvas_dimension {
  /** Constructs a dimension object given the width and height values.
   *
   *  @param width_px The canvas width in pixels.
   *  @param height_px The canvas height in pixels.
   */
  explicit canvas_dimension(double width_px, double height_px)
      : width(std::max(width_px, 1.)), height(std::max(height_px, 1.)) {}

  /// The canvas width in pixels.
  double width{1.};
  /// The canvas height in pixels.
  double height{1.};
};
} // namespace trailblaze::plot