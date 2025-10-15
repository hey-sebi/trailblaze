/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <type_traits>

namespace trailblaze {

/// Provides a view onto a position in 2D space
template <class T>
class position_view_2d {
public:
  using value_type = std::remove_const_t<T>;
  using reference = T&;
  using pointer = T*;

  /** Constructor
   *  @param x x-component of the position.
   *  @param y y-component of the position.
   */
  position_view_2d(T& x, T& y) : x_(&x), y_(&y) {}

  /// Access to the x component of the position
  reference x() const noexcept {
    return *x_;
  }

  /// Access to the y component of the position
  reference y() const noexcept {
    return *y_;
  }

private:
  /// points to the viewed x value
  pointer x_;
  /// points to the viewed y value
  pointer y_;
};

/// Factory function to create a @see position_view_2d
template <class T>
position_view_2d<T> make_position_view_2d(T& x, T& y) {
  return position_view_2d<T>(x, y);
}

} // namespace trailblaze
