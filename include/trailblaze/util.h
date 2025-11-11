/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <cstddef>
#include <cstring>

namespace trailblaze {

/** Checks if a prefix is contained in a string.
 *  @param str The initial string
 *  @param prefix The prefix to check for.
 *  @returns @c true if @p prefix is the start of @p str, @c false otherwise.
 */
constexpr bool starts_with(const char* str, const char* prefix) noexcept {
  if (str == nullptr || prefix == nullptr) {
    return false;
  }

  for (std::size_t i = 0;; ++i) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    const char prefix_char = prefix[i];
    if (prefix_char == '\0') {
      return true; // fully matched the prefix
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    if (str[i] != prefix_char) {
      return false; // mismatch
    }
  }
}

/** Removes a prefix from a string.
 *  @param str The initial string
 *  @param prefix The prefix to remove from @p str.
 *  @returns the modified string if the prefix is contained, the original string otherwise.
 */
constexpr const char* trim_prefix(const char* str, const char* prefix) noexcept {
  if (!starts_with(str, prefix)) {
    return str;
  }
  if (std::strlen(str) == 0) {
    return str;
  }

  std::size_t len = std::strlen(prefix);
  // Return the pointer after the prefix
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  return &(str[len]);
}

} // namespace trailblaze
