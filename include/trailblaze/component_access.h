/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_COMPONENT_ACCESS_H_
#define TRAILBLAZE_COMPONENT_ACCESS_H_

/** @file component_access.h
 *
 *  Contains the general interface used to access a state's individual components.
 *
 *  States that contain a component can implement a specialization for both read and write
 *  access functions if necessary.
 *
 *  The accessors implemented here provide a default. If your state type does not conform
 *  to the default implementation, you can provide your own component accessors.
 *
 */

#include "trailblaze/quaternion.h"

namespace trailblaze {
namespace comp {

// ---------------------- x ----------------------

/** Provides read access to a state's x component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the x component of @p s.
 */
template <typename TState>
double x(const TState& s) noexcept {
  return s.x;
}

/** Provides write access to a state's x component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the x component of @p s.
 */
template <typename TState>
double& x(TState& s) noexcept {
  return s.x;
}

// ---------------------- y ----------------------

/** Provides read access to a state's y component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the y component of @p s.
 */
template <typename TState>
double y(const TState& s) noexcept {
  return s.y;
}

/** Provides write access to a state's y component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the y component of @p s.
 */
template <typename TState>
double& y(TState& s) noexcept {
  return s.y;
}

// ---------------------- z ----------------------

/** Provides read access to a state's z component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the z component of @p s.
 */
template <typename TState>
double z(const TState& s) noexcept {
  return s.z;
}

/** Provides write access to a state's z component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the z component of @p s.
 */
template <typename TState>
double& z(TState& s) noexcept {
  return s.z;
}

// ---------------------- yaw --------------------

/** Provides read access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the yaw component of @p s.
 */
template <typename TState>
double yaw(const TState& s) noexcept {
  return s.yaw;
}

/** Provides write access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the yaw component of @p s.
 */
template <typename TState>
double& yaw(TState& s) noexcept {
  return s.yaw;
}

// ---------------------- orientation as quaternion --------------------

/** Provides read access to a state's orientation component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation component of @p s.
 */
template <typename TState>
quaternion orientation(const TState& s) noexcept {
  return s.orientation;
}

/** Provides write access to a state's orientation component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation component of @p s.
 */
template <typename TState>
quaternion& orientation(TState& s) noexcept {
  return s.orientation;
}

// ---------------------- quaternion x ----------------------

/** Provides read access to a state's orientation-x component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation x-component of @p s.
 */
template <typename TState>
double qx(const TState& s) noexcept {
  return orientation(s).x;
}

/** Provides write access to a state's orientation-x component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation x-component of @p s.
 */
template <typename TState>
double& qx(TState& s) noexcept {
  return orientation(s).x;
}

// ---------------------- quaternion y ----------------------

/** Provides read access to a state's orientation-y component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation x-component of @p s.
 */
template <typename TState>
double qy(const TState& s) noexcept {
  return orientation(s).x;
}

/** Provides write access to a state's orientation-y component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation y-component of @p s.
 */
template <typename TState>
double& qy(TState& s) noexcept {
  return orientation(s).y;
}

// ---------------------- quaternion z ----------------------

/** Provides read access to a state's orientation-z component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation z-component of @p s.
 */
template <typename TState>
double qz(const TState& s) noexcept {
  return orientation(s).z;
}

/** Provides write access to a state's orientation-z component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation z-component of @p s.
 */
template <typename TState>
double& qz(TState& s) noexcept {
  return orientation(s).z;
}

// ---------------------- quaternion w ----------------------

/** Provides read access to a state's orientation-w component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation z-component of @p s.
 */
template <typename TState>
double qw(const TState& s) noexcept {
  return orientation(s).w;
}

/** Provides write access to a state's orientation-w component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation w-component of @p s.
 */
template <typename TState>
double& qw(TState& s) noexcept {
  return orientation(s).w;
}

} // namespace comp
} // namespace trailblaze

#endif