/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <type_traits>

namespace trailblaze {

/// Provides a view onto a position in 3D space
template <class T>
class position_view_3d {
public:
  using value_type = std::remove_const_t<T>;
  using reference = T&;
  using pointer = T*;

  /** Constructor
   *  @param x x-component of the position.
   *  @param y y-component of the position.
   *  @param z z-component of the position.
   */
  position_view_3d(T& x, T& y, T& z) : x_(&x), y_(&y), z_(&z) {}

  /// Access to the x-component of the position
  reference x() const noexcept {
    return *x_;
  }

  /// Access to the y-component of the position
  reference y() const noexcept {
    return *y_;
  }

  /// Access to the z-component of the position
  reference z() const noexcept {
    return *z_;
  }

private:
  /// points to the viewed x value
  pointer x_;
  /// points to the viewed y value
  pointer y_;
  /// points to the viewed z value
  pointer z_;
};

/// Factory function to create a @see position_view_3d
template <class T>
position_view_3d<T> make_position_view_3d(T& x, T& y) {
  return position_view_3d<T>(x, y);
}

} // namespace trailblaze
