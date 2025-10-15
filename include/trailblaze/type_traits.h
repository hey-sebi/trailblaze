/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include "trailblaze/detail/type_traits.h"

namespace trailblaze {

/** @brief Checks if a type has operator<< implemented.
 *  @tparam T any type
 *  @returns @c true if operator<< is present for T, @c false otherwise.
 */
template <typename T>
inline constexpr bool is_ostream_insertable_v = detail::is_ostream_insertable<T>::value;

} // namespace trailblaze
