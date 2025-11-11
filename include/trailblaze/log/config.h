/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

/**
 * @brief Compile-time selection of the active logging backend.
 *
 * In order to integrate a custom logging backend into Trailblaze, you need to specify the
 * header that contains a backend implementation and the full qualified name of the
 * logger.
 *
 * See the logging example and the associacted CMakeLists.txt for more information!
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
