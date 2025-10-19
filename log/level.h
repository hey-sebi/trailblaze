/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <cstdint>

namespace trailblaze::log {

/**
 * @brief Log severity levels in increasing order of importance.
 */
enum class level : std::uint8_t {
  trace = 0, ///< Very verbose, internal tracing.
  debug,     ///< Debug information for developers.
  info,      ///< General informational messages.
  warn,      ///< Potentially harmful situation.
  error,     ///< Error that did not stop the program.
  critical,  ///< Critical error — system may be unable to continue.
  off        ///< Disable logging.
};

} // namespace trailblaze::log
