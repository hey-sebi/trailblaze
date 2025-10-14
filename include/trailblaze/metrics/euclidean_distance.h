/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_METRICS_EUCLIDEAN_DISTANCE_H_
#define TRAILBLAZE_METRICS_EUCLIDEAN_DISTANCE_H_
// STL
#include <cmath>
// This library
#include <trailblaze/component_access.h>
#include <trailblaze/state_traits.h>

namespace trailblaze {

/// Trait for Euclidean distance calculation in the 2D space.
struct EuclideanDistance2D {
  /** Calculates the Euclidean distance in the 2D space between two states.
   *  @tparam TState A state that has at least X and Y components.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const {
    static_assert(has_xy_v<TState>, "EuclideanDistance2D: state needs to have X and Y components");

    const double dx = comp::X(lhs) - comp::X(rhs);
    const double dy = comp::Y(lhs) - comp::Y(rhs);
    return std::hypot(dx, dy);
  }
};

/// Trait for Euclidean distance calculation in the 3D space.
struct EuclideanDistance3D {
  /** Calculates the Euclidean distance in the 3D space between two states.
   *  @tparam TState A state that has at least X, Y and Z components.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const {
    static_assert(has_xyz_v<TState>,
                  "EuclideanDistance3D: state needs to have X, Y and Z components");

    const double dx = comp::X(lhs) - comp::X(rhs);
    const double dy = comp::Y(lhs) - comp::Y(rhs);
    const double dz = comp::Z(lhs) - comp::Z(rhs);
    return std::hypot(dx, dy, dz);
  }
};
} // namespace trailblaze

#endif
