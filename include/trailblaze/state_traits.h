/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include "trailblaze/detail/state_traits.h"

namespace trailblaze {

/** Trait to check if a state has x and y components.
 *  @tparam T The state type
 *  @returns @c true if the state has the components, @c false otherwise.
 */
template <typename T>
inline constexpr bool has_xy_v = detail::has_xy<T>::value;

template <typename T>
inline constexpr bool has_yaw_v = detail::has_yaw<T>::value;

template <typename T>
constexpr bool has_xyz_v = detail::has_xyz<T>::value;

template <typename T>
constexpr bool has_quat_v = detail::has_quat<T>::value;

/** Bundles state traits.
 *  @tparam T State type
 *
 *   Usage example:
 *  @code
 *    struct SomeState
 *    {
 *      double x;
 *      double y;
 *    };
 *
 *    if constexpr (state_traits<SomeState>::has_xy)
 *    {
 *       // handle components
 *    }
 *  @endcode
 */
template <typename T>
struct state_traits {
  static constexpr bool has_xy = has_xy_v<T>;
  static constexpr bool has_yaw = has_yaw_v<T>;
  static constexpr bool has_xyz = has_xyz_v<T>;
  static constexpr bool has_quaternion = has_quat_v<T>;
};

} // namespace trailblaze
