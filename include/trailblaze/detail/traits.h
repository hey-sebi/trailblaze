#ifndef TRAILBLAZE_DETAIL_TRAITS_H_
#define TRAILBLAZE_DETAIL_TRAITS_H_

#include <type_traits>
#include <utility>

namespace trailblaze {
namespace detail {

template <typename T, typename = void>
struct has_xy : std::false_type
{
};

template <typename T>
struct has_xy<T,
              std::void_t<decltype(std::declval<T&>().x), decltype(std::declval<T&>().y)>>
    : std::true_type
{
};

template <typename S, typename = void>
struct has_yaw : std::false_type
{
};

template <typename S>
struct has_yaw<S, std::void_t<decltype(std::declval<S>().yaw)>> : std::true_type
{
};

template <typename S, typename = void>
struct has_xyz : std::false_type
{
};

template <typename S>
struct has_xyz<S,
               std::void_t<decltype(std::declval<S>().x), decltype(std::declval<S>().y),
                           decltype(std::declval<S>().z)>> : std::true_type
{
};

template <typename S, typename = void>
struct has_quat : std::false_type
{
};

template <typename S>
struct has_quat<S, std::void_t<decltype(std::declval<S>().rotation.x),
                               decltype(std::declval<S>().rotation.y),
                               decltype(std::declval<S>().rotation.z),
                               decltype(std::declval<S>().rotation.w)>> : std::true_type
{
};
}  // namespace detail

}  // namespace trailblaze

#endif