/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <cstdio>
#include <string_view>

#include "trailblaze/log/level.h"
#include "trailblaze/log/source_location.h"

namespace app {

/**
 * @brief Minimal example logging backend printing to stderr.
 *
 * Enable/disable levels here at compile time. Disabled levels are compiled out
 * from call sites in trailblaze when this backend is active.
 */
struct custom_logger {
  static constexpr bool level_trace_enabled = true;
  static constexpr bool level_debug_enabled = true;
  static constexpr bool level_info_enabled = true;
  static constexpr bool level_warn_enabled = true;
  static constexpr bool level_error_enabled = true;
  static constexpr bool level_critical_enabled = true;

  /// @brief Log a message without source location.
  static void log(::trailblaze::log::level lvl, std::string_view msg) noexcept {
    std::fputs(prefix(lvl), stderr);
    std::fwrite(msg.data(), 1, msg.size(), stderr);
    std::fputc('\n', stderr);
  }

  /// @brief Log a message with source location.
  static void log(::trailblaze::log::level lvl, std::string_view msg,
                  ::trailblaze::log::source_location loc) noexcept {
    std::fprintf(stderr, "%s%s (%s:%u)\n", prefix(lvl), std::string(msg).c_str(), loc.file,
                 loc.line);
  }

private:
  /**
   * @brief Generates a log message's prefix derived from a log level
   *
   * @param lvl The log level
   * @return A string representation for the log level
   */
  static const char* prefix(::trailblaze::log::level lvl) noexcept {
    using ::trailblaze::log::level;
    switch (lvl) {
    case level::trace:
      return "[   trace] ";
    case level::debug:
      return "[   debug] ";
    case level::info:
      return "[    info] ";
    case level::warn:
      return "[ warning] ";
    case level::error:
      return "[   error] ";
    case level::critical:
      return "[critical] ";
    default:
      return "";
    }
  }
};

} // namespace app
