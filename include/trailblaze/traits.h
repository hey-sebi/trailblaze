#ifndef TRAILBLAZE_TRAITS_H_
#define TRAILBLAZE_TRAITS_H_

#include <type_traits>
#include <utility>

namespace trailblaze {

template <typename...>
using void_t = void;

// Basic field presence detectors for common atoms.
template <typename S, typename = void>
struct has_xy : std::false_type {};
template <typename S>
struct has_xy<S, void_t<decltype(std::declval<S>().x),
                        decltype(std::declval<S>().y)>> : std::true_type {};
template <typename S>
constexpr bool kHasXy = has_xy<S>::value;

template <typename S, typename = void>
struct has_yaw : std::false_type {};
template <typename S>
struct has_yaw<S, void_t<decltype(std::declval<S>().yaw)>> : std::true_type {};
template <typename S>
constexpr bool kHasYaw = has_yaw<S>::value;

template <typename S, typename = void>
struct has_xyz : std::false_type {};
template <typename S>
struct has_xyz<S, void_t<decltype(std::declval<S>().x),
                         decltype(std::declval<S>().y),
                         decltype(std::declval<S>().z)>> : std::true_type {};
template <typename S>
constexpr bool kHasXyz = has_xyz<S>::value;

template <typename S, typename = void>
struct has_quat : std::false_type {};
template <typename S>
struct has_quat<S, void_t<decltype(std::declval<S>().qx),
                          decltype(std::declval<S>().qy),
                          decltype(std::declval<S>().qz),
                          decltype(std::declval<S>().qw)>> : std::true_type {};
template <typename S>
constexpr bool kHasQuat = has_quat<S>::value;

// Central traits, user-specializable per type if needed.
template <typename S>
struct StateTraits {
  static constexpr bool kHasXy = kHasXy<S>;
  static constexpr bool kHasYaw = kHasYaw<S>;
  static constexpr bool kHasXyz = kHasXyz<S>;
  static constexpr bool kHasQuat = kHasQuat<S>;
};

}  // namespace trailblaze

#endif  // TRAILBLAZE_TRAITS_H_
