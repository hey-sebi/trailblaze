/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <string_view>
#include <type_traits>

#include "trailblaze/log/level.h"
#include "trailblaze/log/source_location.h"

/** @file detect.h
 *
 *  Contains traits to detect which logging capabilities exist.
 *  Depending on the eventually user-supplied logger, we can
 *  detect different features automatically.
 */

namespace trailblaze::log::detail {

/**
 * @brief Trait: backend has string sink log(level, string_view).
 */
template <class B, class = void>
struct has_string_sink : std::false_type {};
template <class B>
struct has_string_sink<B, std::void_t<decltype(std::declval<B&>().log(
                              std::declval<level>(), std::declval<std::string_view>()))>>
    : std::true_type {};
template <class B>
inline constexpr bool has_string_sink_v = has_string_sink<B>::value;

/**
 * @brief Trait: backend has string sink with source location.
 */
template <class B, class = void>
struct has_string_sink_loc : std::false_type {};
template <class B>
struct has_string_sink_loc<B, std::void_t<decltype(std::declval<B&>().log(
                                  std::declval<level>(), std::declval<std::string_view>(),
                                  std::declval<source_location>()))>> : std::true_type {};
template <class B>
inline constexpr bool has_string_sink_loc_v = has_string_sink_loc<B>::value;

/**
 * @brief Compile-time check whether a given level is enabled on backend TBackend.
 */
template <class TBackend>
constexpr bool level_enabled(level lvl) {
  switch (lvl) {
  case level::trace:
    return TBackend::level_trace_enabled;
  case level::debug:
    return TBackend::level_debug_enabled;
  case level::info:
    return TBackend::level_info_enabled;
  case level::warn:
    return TBackend::level_warn_enabled;
  case level::error:
    return TBackend::level_error_enabled;
  case level::critical:
    return TBackend::level_critical_enabled;
  default:
    return false;
  }
}

} // namespace trailblaze::log::detail
