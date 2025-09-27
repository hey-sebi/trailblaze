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
double X(const TState& s) noexcept
{
  return s.x;
}

/** Provides write access to a state's x component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the x component of @p s.
 */
template <typename TState>
double& X(TState& s) noexcept
{
  return s.x;
}

// ---------------------- y ----------------------

/** Provides read access to a state's y component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the y component of @p s.
 */
template <typename TState>
double Y(const TState& s) noexcept
{
  return s.y;
}

/** Provides write access to a state's y component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the y component of @p s.
 */
template <typename TState>
double& Y(TState& s) noexcept
{
  return s.y;
}

// ---------------------- z ----------------------

/** Provides read access to a state's z component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the z component of @p s.
 */
template <typename TState>
double Z(const TState& s) noexcept
{
  return s.z;
}

/** Provides write access to a state's z component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the z component of @p s.
 */
template <typename TState>
double& Z(TState& s) noexcept
{
  return s.z;
}

// ---------------------- yaw --------------------

/** Provides read access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the yaw component of @p s.
 */
template <typename TState>
double Yaw(const TState& s) noexcept
{
  return s.yaw;
}

/** Provides write access to a state's yaw component.
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the yaw component of @p s.
 */
template <typename TState>
double& Yaw(TState& s) noexcept
{
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
Quaternion Orientation(const TState& s) noexcept
{
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
Quaternion& Orientation(TState& s) noexcept
{
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
double Qx(const TState& s) noexcept
{
  return Orientation(s).x;
}

/** Provides write access to a state's orientation-x component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation x-component of @p s.
 */
template <typename TState>
double& Qx(TState& s) noexcept
{
  return Orientation(s).x;
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
double Qy(const TState& s) noexcept
{
  return Orientation(s).x;
}

/** Provides write access to a state's orientation-y component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation y-component of @p s.
 */
template <typename TState>
double& Qy(TState& s) noexcept
{
  return Orientation(s).y;
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
double Qz(const TState& s) noexcept
{
  return Orientation(s).z;
}

/** Provides write access to a state's orientation-z component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation z-component of @p s.
 */
template <typename TState>
double& Qz(TState& s) noexcept
{
  return Orientation(s).z;
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
double Qw(const TState& s) noexcept
{
  return Orientation(s).w;
}

/** Provides write access to a state's orientation-w component.
 *  This applies to states that model the orientation using a quaternion.
 *
 *  @tparam TState The state type.
 *  @param s The accessed state.
 *  @returns the orientation w-component of @p s.
 */
template <typename TState>
double& Qw(TState& s) noexcept
{
  return Orientation(s).w;
}

}  // namespace comp
}  // namespace trailblaze

#endif