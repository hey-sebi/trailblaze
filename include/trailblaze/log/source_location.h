/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <cstdint>

// Fallbacks for compilers without __builtin_*
#ifndef TB_HAS_BUILTIN_SOURCE_LOCATION
#if defined(__clang__) || defined(__GNUC__)
#define TB_HAS_BUILTIN_SOURCE_LOCATION 1
#else
#define TB_HAS_BUILTIN_SOURCE_LOCATION 0
#endif
#endif

namespace trailblaze::log {

/**
 *  @brief Minimal backport of C++20 std::source_location for C++17.
 *
 *  This captures file, function, and line at the call site.
 */
struct source_location {
  /// @brief Default-constructed empty location.
  constexpr source_location() = default;

  /// @brief Construct an explicit source location.
  constexpr source_location(const char* filename, const char* function_name,
                            std::uint32_t line_number)
      : file(filename), function(function_name), line(line_number) {}

  /**
   * @brief Capture the current call site.
   * @return A location built from compiler intrinsics or fallbacks.
   */
  static constexpr source_location current(
#if TB_HAS_BUILTIN_SOURCE_LOCATION
      const char* filename = __builtin_FILE(), const char* function_name = __builtin_FUNCTION(),
      std::uint32_t line_number = __builtin_LINE()
#else
      const char* filename = __FILE__, const char* function_name = __func__,
      std::uint32_t line_number = __LINE__
#endif
  ) {
    return source_location{filename, function_name, line_number};
  }

  const char* file = "";
  const char* function = "";
  std::uint32_t line = 0;
};

} // namespace trailblaze::log
