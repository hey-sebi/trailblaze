/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_DETAIL_STATE_TRAITS_H_
#define TRAILBLAZE_DETAIL_STATE_TRAITS_H_

#include <type_traits>
#include <utility>

namespace trailblaze {
namespace detail {

template <typename TState, typename = void>
struct has_xy : std::false_type {};

template <typename TState>
struct has_xy<TState,
              std::void_t<decltype(std::declval<TState&>().x), decltype(std::declval<TState&>().y)>>
    : std::true_type {};

template <typename TState, typename = void>
struct has_yaw : std::false_type {};

template <typename TState>
struct has_yaw<TState, std::void_t<decltype(std::declval<TState>().yaw)>> : std::true_type {};

template <typename TState, typename = void>
struct has_xyz : std::false_type {};

template <typename TState>
struct has_xyz<TState,
               std::void_t<decltype(std::declval<TState>().x),
                           decltype(std::declval<TState>().y),
                           decltype(std::declval<TState>().z)>> : std::true_type {};

template <typename TState, typename = void>
struct has_quat : std::false_type {};

template <typename TState>
struct has_quat<TState,
                std::void_t<decltype(std::declval<TState>().rotation.x),
                            decltype(std::declval<TState>().rotation.y),
                            decltype(std::declval<TState>().rotation.z),
                            decltype(std::declval<TState>().rotation.w)>> : std::true_type {};

} // namespace detail
} // namespace trailblaze

#endif