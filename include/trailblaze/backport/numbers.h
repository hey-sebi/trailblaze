/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#if defined(__has_include)
#if __has_include(<numbers>) && __cplusplus >= 202002L
#include <numbers>
#define TRAILBLAZE_HAS_STD_NUMBERS 1
#endif
#endif

namespace trailblaze::numbers {
#if TRAILBLAZE_HAS_STD_NUMBERS

using pi = std::numbers::pi;

#else

/// Substitute for @see std::numbers::pi.
inline constexpr double pi = 3.14159265358979323846;

#endif

} // namespace trailblaze::numbers
