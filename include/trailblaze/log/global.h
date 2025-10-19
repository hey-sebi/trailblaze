/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include "trailblaze/log/config.h"

namespace trailblaze::log {

/**
 * @brief Accessor for the logger backend instance.
 *
 * The object is lazily-initialized on first use and has static storage duration.
 * If the selected backend is @ref null_logger, compilers will elide calls under
 * the compile-time level guards in the public API.
 */
inline log_config::backend& logger() {
  static log_config::backend instance{};
  return instance;
}

} // namespace trailblaze::log
