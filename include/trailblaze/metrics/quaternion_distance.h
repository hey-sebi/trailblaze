/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include "trailblaze/quaternion.h"

namespace trailblaze {

/// Trait for quaternion distance calculation.
struct quaternion_distance {
  /** Calculates the quaternion distance between two states.
   *  @tparam TState A state that has at least an quaternion orientation component.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const {
    static_assert(has_quat_v<TState>,
                  "quaternion_distance: state needs to have a quaternion component");

    quaternion diff;
    diff.x = comp::qx(lhs) - comp::qx(rhs);
    diff.y = comp::qy(lhs) - comp::qy(rhs);
    diff.z = comp::qz(lhs) - comp::qz(rhs);
    diff.w = comp::qw(lhs) - comp::qw(rhs);
    return norm(diff);
  }
};

} // namespace trailblaze
