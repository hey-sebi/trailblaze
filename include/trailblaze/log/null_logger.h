/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <string_view>

#include "trailblaze/log/level.h"
#include "trailblaze/log/source_location.h"

namespace trailblaze::log {

/**
 * @brief Compile-time disabled backend: all levels are off.
 *
 * When this backend is selected, guarded logging sites are
 * not instantiated, yielding true "null overhead".
 */
struct null_logger {
  static constexpr bool level_trace_enabled = false;
  static constexpr bool level_debug_enabled = false;
  static constexpr bool level_info_enabled = false;
  static constexpr bool level_warn_enabled = false;
  static constexpr bool level_error_enabled = false;
  static constexpr bool level_critical_enabled = false;

  /// @brief String sink (never called because all levels are disabled).
  void log(level log_level, std::string_view message) noexcept {}

  /// @brief String sink with source location (never called).
  void log(level log_level, std::string_view message, source_location origin) noexcept {}
};

} // namespace trailblaze::log
