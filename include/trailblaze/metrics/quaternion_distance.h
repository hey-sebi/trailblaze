#ifndef TRAILBLAZE_METRICS_QUATERNION_DISTANCE_H_
#define TRAILBLAZE_METRICS_QUATERNION_DISTANCE_H_
#include "trailblaze/quaternion.h"

namespace trailblaze {

/// Trait for quaternion distance calculation.
struct QuaternionDistance
{
  /** Calculates the quaternion distance between two states.
   *  @tparam TState A state that has at least an quaternion orientation component.
   *  @param lhs The first state.
   *  @param rhs The second state.
   *  @returns The distance value.
   */
  template <typename TState>
  double operator()(const TState& lhs, const TState& rhs) const
  {
    static_assert(has_quat_v<TState>,
                  "QuaternionDistance: state needs to have a quaternion component");

    Quaternion diff;
    diff.x = comp::Qx(lhs) - comp::Qx(rhs);
    diff.y = comp::Qy(lhs) - comp::Qy(rhs);
    diff.z = comp::Qz(lhs) - comp::Qz(rhs);
    diff.w = comp::Qw(lhs) - comp::Qw(rhs);
    return Norm(diff);
  }
};

}  // namespace trailblaze

#endif