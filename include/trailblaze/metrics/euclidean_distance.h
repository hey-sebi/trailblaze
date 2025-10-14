/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_METRICS_EUCLIDEAN_DISTANCE_H_
#define TRAILBLAZE_METRICS_EUCLIDEAN_DISTANCE_H_
// STL
#include <cmath>

#include "trailblaze/component_access.h"
#include "trailblaze/state_traits.h"

namespace trailblaze {

/// Trait for Euclidean distance calculation in the 2D space.
struct euclidean_distance_2d {
  /** Calculates the Euclidean distance in the 2D space between two states.
   *  @tparam TState A state that has at least x and y components.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const {
    static_assert(has_xy_v<TState>,
                  "euclidean_distance_2d: state needs to have X and y components");

    const double dx = comp::x(lhs) - comp::x(rhs);
    const double dy = comp::y(lhs) - comp::y(rhs);
    return std::hypot(dx, dy);
  }
};

/// Trait for Euclidean distance calculation in the 3D space.
struct euclidean_distance_3d {
  /** Calculates the Euclidean distance in the 3D space between two states.
   *  @tparam TState A state that has at least x, y and z components.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const {
    static_assert(has_xyz_v<TState>,
                  "euclidean_distance_3d: state needs to have X, y and z components");

    const double dx = comp::x(lhs) - comp::x(rhs);
    const double dy = comp::y(lhs) - comp::y(rhs);
    const double dz = comp::z(lhs) - comp::z(rhs);
    return std::hypot(dx, dy, dz);
  }
};

} // namespace trailblaze

#endif
