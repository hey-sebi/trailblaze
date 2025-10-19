/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <cstdint>

namespace trailblaze::log {

enum class level : std::uint8_t { trace = 0, debug, info, warn, error, critical, off };

} // namespace trailblaze::log
