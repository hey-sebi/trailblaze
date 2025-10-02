/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_POSITION_VIEW_2D_H_
#define TRAILBLAZE_POSITION_VIEW_2D_H_
#include <type_traits>

namespace trailblaze {

/// Provides a view onto a position in 2D space
template <class T>
class PositionView2D
{
 public:
  using value_type = std::remove_const_t<T>;
  using reference = T&;
  using pointer = T*;

  /** Constructor
   *  @param x X-component of the position.
   *  @param y Y-component of the position.
   */
  PositionView2D(T& x, T& y) : x_(&x), y_(&y)
  {
  }

  /// Access to the X component of the position
  reference X() const noexcept
  {
    return *x_;
  }

  /// Access to the Y component of the position
  reference Y() const noexcept
  {
    return *y_;
  }

 private:
  /// points to the viewed x value
  pointer x_;
  /// points to the viewed y value
  pointer y_;
};

/// Factory function to create a @see PositionView2D
template <class U>
auto MakePositionView2D(U& x, U& y) -> PositionView2D<U>
{
  return PositionView2D<U>(x, y);
}

}  // namespace trailblaze

#endif