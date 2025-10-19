/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include "trailblaze/log/detail/detect.h"
#include "trailblaze/log/global.h"
#include "trailblaze/log/level.h"
#include "trailblaze/log/source_location.h"

#if TRAILBLAZE_WITH_FMT
#include <fmt/format.h>
#include <string>
#endif

namespace trailblaze::log {
namespace detail {

/**
 * @brief Helper to dispatch eager fmt calls into a backend string sink.
 *
 * We keep the backend contract simple: a string sink is sufficient.
 * If a backend offers a location-aware sink, we prefer that.
 *
 * @tparam B Backend type.
 * @tparam Ts Format argument pack.
 */
#if TRAILBLAZE_WITH_FMT
template <class B, class... Ts>
inline void emit_fmt(level lvl, source_location loc, fmt::format_string<Ts...> f, Ts&&... ts) {
  if constexpr (has_string_sink_loc_v<B>) {
    auto msg = fmt::format(f, static_cast<Ts&&>(ts)...);
    logger().log(lvl, msg, loc);
  } else if constexpr (has_string_sink_v<B>) {
    auto msg = fmt::format(f, static_cast<Ts&&>(ts)...);
    logger().log(lvl, msg);
  } else {
    /* No compatible sink: drop. */
  }
}
#endif

} // namespace detail

/* ---------- fmt-style API ---------- */

#if TRAILBLAZE_WITH_FMT
/** @name Eager fmt-style logging
 *  @brief Formatting occurs only when the level is enabled at compile time.
 *  @{
 */
template <class... Ts>
inline void log_trace(fmt::format_string<Ts...> f, Ts&&... ts) {
  using B = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<B>(level::trace)) {
    detail::emit_fmt<B>(level::trace, source_location::current(), f, static_cast<Ts&&>(ts)...);
  }
}

template <class... Ts>
inline void log_debug(fmt::format_string<Ts...> f, Ts&&... ts) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::debug)) {
    detail::emit_fmt<logging_backend>(level::debug, source_location::current(), f,
                                      static_cast<Ts&&>(ts)...);
  }
}

template <class... Ts>
inline void log_info(fmt::format_string<Ts...> f, Ts&&... ts) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::info)) {
    detail::emit_fmt<logging_backend>(level::info, source_location::current(), f,
                                      static_cast<Ts&&>(ts)...);
  }
}

template <class... Ts>
inline void log_warn(fmt::format_string<Ts...> f, Ts&&... ts) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::warn)) {
    detail::emit_fmt<logging_backend>(level::warn, source_location::current(), f,
                                      static_cast<Ts&&>(ts)...);
  }
}

template <class... Ts>
inline void log_error(fmt::format_string<Ts...> f, Ts&&... ts) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::error)) {
    detail::emit_fmt<logging_backend>(level::error, source_location::current(), f,
                                      static_cast<Ts&&>(ts)...);
  }
}

template <class... Ts>
inline void log_critical(fmt::format_string<Ts...> f, Ts&&... ts) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::critical)) {
    detail::emit_fmt<logging_backend>(level::critical, source_location::current(), f,
                                      static_cast<Ts&&>(ts)...);
  }
}
/** @} */
#endif /* TRAILBLAZE_WITH_FMT */

/* ---------- Lazy fmt-style API (avoid arg eval entirely) ---------- */

/**
 * @brief Lazy logging: supplier is evaluated only when the level is enabled.
 *
 * @tparam F Callable returning std::string (commonly from fmt::format()).
 */
template <class F>
inline void log_trace_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::trace)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::trace, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::trace, s);
    }
#endif
  }
}

template <class F>
inline void log_debug_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::debug)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::debug, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::debug, s);
    }
#endif
  }
}

template <class F>
inline void log_info_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::info)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::info, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::info, s);
    }
#endif
  }
}

template <class F>
inline void log_warn_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::warn)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::warn, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::warn, s);
    }
#endif
  }
}

template <class F>
inline void log_error_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::error)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::error, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::error, s);
    }
#endif
  }
}

template <class F>
inline void log_critical_lazy(F&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::critical)) {
#if TRAILBLAZE_WITH_FMT
    auto s = make_message();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(level::critical, s, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(level::critical, s);
    }
#endif
  }
}

} // namespace trailblaze::log
