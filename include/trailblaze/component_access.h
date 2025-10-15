/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
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

namespace trailblaze::comp {

// ---------------------- x ----------------------

/** Provides read access to a state's x component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the x component of @p state.
 */
template <typename TState>
double x(const TState& state) noexcept {
  return state.x;
}

/** Provides write access to a state's x component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the x component of @p state.
 */
template <typename TState>
double& x(TState& state) noexcept {
  return state.x;
}

// ---------------------- y ----------------------

/** Provides read access to a state's y component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the y component of @p state.
 */
template <typename TState>
double y(const TState& state) noexcept {
  return state.y;
}

/** Provides write access to a state's y component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the y component of @p state.
 */
template <typename TState>
double& y(TState& state) noexcept {
  return state.y;
}

// ---------------------- z ----------------------

/** Provides read access to a state's z component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the z component of @p state.
 */
template <typename TState>
double z(const TState& state) noexcept {
  return state.z;
}

/** Provides write access to a state's z component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the z component of @p state.
 */
template <typename TState>
double& z(TState& state) noexcept {
  return state.z;
}

// ---------------------- yaw --------------------

/** Provides read access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the yaw component of @p state.
 */
template <typename TState>
double yaw(const TState& state) noexcept {
  return state.yaw;
}

/** Provides write access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the yaw component of @p state.
 */
template <typename TState>
double& yaw(TState& state) noexcept {
  return state.yaw;
}

// ---------------------- orientation as quaternion --------------------

/** Provides read access to a state's orientation component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation component of @p state.
 */
template <typename TState>
quaternion orientation(const TState& state) noexcept {
  return state.orientation;
}

/** Provides write access to a state's orientation component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation component of @p state.
 */
template <typename TState>
quaternion& orientation(TState& state) noexcept {
  return state.orientation;
}

// ---------------------- quaternion x ----------------------

/** Provides read access to a state's orientation-x component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation x-component of @p state.
 */
template <typename TState>
double qx(const TState& state) noexcept {
  return orientation(state).x;
}

/** Provides write access to a state's orientation-x component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation x-component of @p state.
 */
template <typename TState>
double& qx(TState& state) noexcept {
  return orientation(state).x;
}

// ---------------------- quaternion y ----------------------

/** Provides read access to a state's orientation-y component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation x-component of @p state.
 */
template <typename TState>
double qy(const TState& state) noexcept {
  return orientation(state).x;
}

/** Provides write access to a state's orientation-y component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation y-component of @p state.
 */
template <typename TState>
double& qy(TState& state) noexcept {
  return orientation(state).y;
}

// ---------------------- quaternion z ----------------------

/** Provides read access to a state's orientation-z component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation z-component of @p state.
 */
template <typename TState>
double qz(const TState& state) noexcept {
  return orientation(state).z;
}

/** Provides write access to a state's orientation-z component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation z-component of @p state.
 */
template <typename TState>
double& qz(TState& state) noexcept {
  return orientation(state).z;
}

// ---------------------- quaternion w ----------------------

/** Provides read access to a state's orientation-w component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation z-component of @p state.
 */
template <typename TState>
double qw(const TState& state) noexcept {
  return orientation(state).w;
}

/** Provides write access to a state's orientation-w component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param state The accessed state.
 *  @returns the orientation w-component of @p state.
 */
template <typename TState>
double& qw(TState& state) noexcept {
  return orientation(state).w;
}

} // namespace trailblaze::comp
