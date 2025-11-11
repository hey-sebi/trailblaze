/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstdint>

namespace trailblaze::log {

/**
 *  Enumerates logging levels supported by trailblaze.
 *  Logging levels range from trace to critical:
 *
 *  - trace: Most verbose logging level for messages with lowest priority.
 *  - critical: Level with highest priority for situations that the system cannot recover from.
 *  - off: Logging is not desired.
 */
enum class level : std::uint8_t {
  /// Most verbose logging level for messages with lowest priority.
  trace = 0,
  /// Verbose messages required for debugging context.
  debug,
  /// Logs regular application flow/progress.
  info,
  /// Warnings for exceptional/noticable situations. Those might or might not indicate issues.
  warn,
  /// Reports detection of errors or states that are unfavorable.
  error,
  /// Level with highest priority for situations that the system cannot recover from.
  critical,
  /// Used to disable logging from a user perspective.
  off
};

} // namespace trailblaze::log
