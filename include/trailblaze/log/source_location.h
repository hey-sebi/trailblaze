/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <cstdint>
#include <iostream>

#include "trailblaze/util.h"

// Fallbacks for compilers without __builtin_*
#ifndef TB_HAS_BUILTIN_SOURCE_LOCATION
#if defined(__clang__) || defined(__GNUC__)
#define TB_HAS_BUILTIN_SOURCE_LOCATION 1
#else
#define TB_HAS_BUILTIN_SOURCE_LOCATION 0
#endif
#endif

#ifndef TRAILBLAZE_SOURCE_DIR
#define TRAILBLAZE_SOURCE_DIR ""
#endif
#ifndef TRAILBLAZE_INCLUDE_DIR
#define TRAILBLAZE_INCLUDE_DIR ""
#endif

namespace trailblaze::log {

constexpr const char* strip_filepath(const char* str) {
  if (starts_with(str, TRAILBLAZE_SOURCE_DIR)) {
    return trim_prefix(str, TRAILBLAZE_SOURCE_DIR);
  }
  if (starts_with(str, TRAILBLAZE_INCLUDE_DIR)) {
    return trim_prefix(str, TRAILBLAZE_INCLUDE_DIR);
  }
  std::cerr << "does not start:" << str << ", " << TRAILBLAZE_SOURCE_DIR << ", "
            << TRAILBLAZE_INCLUDE_DIR << std::endl;
  return str;
}

/**
 *  @brief Minimal backport of C++20 std::source_location for C++17.
 *
 *  This captures the calling filename, line and function name.
 */
struct source_location {
  /// @brief Default-constructed empty location.
  constexpr source_location() = default;

  /// @brief Construct an explicit source location.
  constexpr source_location(const char* filename, std::uint32_t line_number,
                            const char* function_name)
      : file(strip_filepath(filename)), line(line_number), function(function_name) {}

  /**
   * @brief Capture the current call site.
   * @return A location built from compiler intrinsics or fallbacks.
   */
  static constexpr source_location current(
#if TB_HAS_BUILTIN_SOURCE_LOCATION
      const char* filename = __builtin_FILE(), const char* function_name = __builtin_FUNCTION(),
      std::uint32_t line_number = __builtin_LINE()
#else
      const char* filename = __FILE__, std::uint32_t line_number = __LINE__,
      const char* function_name = __func__
#endif
  ) {
    return source_location{filename, line_number, function_name};
  }

  const char* file = "";
  std::uint32_t line = 0;
  const char* function = "";
};

} // namespace trailblaze::log
