/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

/**
 * @brief Compile-time selection of the active logging backend.
 *
 * You can either:
 *  - Define TRAILBLAZE_LOG_BACKEND to a fully-qualified type (e.g. ::app::my_logger)
 *    and ensure that type is declared before including any Trailblaze log headers, or
 *  - Define TRAILBLAZE_LOG_BACKEND_HEADER to a header path (as a string literal)
 *    so Trailblaze includes it before forming the alias.
 *
 * Examples:
 *   -DTRAILBLAZE_LOG_BACKEND_HEADER=\"app/my_logger.h\"
 *   -DTRAILBLAZE_LOG_BACKEND=::app::my_logger
 */

#ifdef TRAILBLAZE_LOG_BACKEND_HEADER
#include TRAILBLAZE_LOG_BACKEND_HEADER
#else
#include "trailblaze/log/null_logger.h"
#endif

namespace trailblaze::log_config {

#ifndef TRAILBLAZE_LOG_BACKEND
// By default we use a null logger that is compiled away.
using backend = ::trailblaze::log::null_logger;
#else
using backend = TRAILBLAZE_LOG_BACKEND;
#endif

} // namespace trailblaze::log_config
