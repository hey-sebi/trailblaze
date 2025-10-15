/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <ostream>
#include <type_traits>

namespace trailblaze::detail {

// Primary template: not stream-insertable.
template <typename T, typename = void>
struct is_ostream_insertable : std::false_type {};

// Specialization: valid if `std::ostream << const T&` is well-formed.
template <typename T>
struct is_ostream_insertable<
    T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

} // namespace trailblaze::detail
