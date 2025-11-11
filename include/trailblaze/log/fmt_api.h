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
inline void emit_fmt(level lvl, source_location loc, fmt::format_string<Ts...> format, Ts&&... ts) {
  if constexpr (has_string_sink_loc_v<B>) {
    auto msg = fmt::format(format, static_cast<Ts&&>(ts)...);
    logger().log(lvl, msg, loc);
  } else if constexpr (has_string_sink_v<B>) {
    auto msg = fmt::format(format, static_cast<Ts&&>(ts)...);
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
template <class... TArgs>
inline void log_trace(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using backend_type = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<backend_type>(level::trace)) {
    detail::emit_fmt<backend_type>(level::trace, source_location::current(), format,
                                   static_cast<TArgs&&>(args)...);
  }
}

template <class... TArgs>
inline void log_debug(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::debug)) {
    detail::emit_fmt<logging_backend>(level::debug, source_location::current(), format,
                                      static_cast<TArgs&&>(args)...);
  }
}

template <class... TArgs>
inline void log_info(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::info)) {
    detail::emit_fmt<logging_backend>(level::info, source_location::current(), format,
                                      static_cast<TArgs&&>(args)...);
  }
}

template <class... TArgs>
inline void log_warn(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::warn)) {
    detail::emit_fmt<logging_backend>(level::warn, source_location::current(), format,
                                      static_cast<TArgs&&>(args)...);
  }
}

template <class... TArgs>
inline void log_error(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::error)) {
    detail::emit_fmt<logging_backend>(level::error, source_location::current(), format,
                                      static_cast<TArgs&&>(args)...);
  }
}

template <class... TArgs>
inline void log_critical(fmt::format_string<TArgs...> format, TArgs&&... args) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::critical)) {
    detail::emit_fmt<logging_backend>(level::critical, source_location::current(), format,
                                      static_cast<TArgs&&>(args)...);
  }
}

#endif /* TRAILBLAZE_WITH_FMT */

/* ---------- Lazy fmt-style API (avoid arg eval entirely) ---------- */

/**
 * @brief Lazy logging: supplier is evaluated only when the level is enabled.
 *
 * @tparam TFunc Callable returning std::string (commonly from fmt::format()).
 */
template <class TFunc>
inline void log_trace_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::trace)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::trace, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::trace, msg);
    }
#endif
  }
}

template <class TFunc>
inline void log_debug_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::debug)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::debug, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::debug, msg);
    }
#endif
  }
}

template <class TFunc>
inline void log_info_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::info)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::info, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::info, msg);
    }
#endif
  }
}

template <class TFunc>
inline void log_warn_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::warn)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::warn, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::warn, msg);
    }
#endif
  }
}

template <class TFunc>
inline void log_error_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::error)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::error, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::error, msg);
    }
#endif
  }
}

template <class TFunc>
inline void log_critical_lazy(TFunc&& make_message) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(level::critical)) {
#if TRAILBLAZE_WITH_FMT
    auto msg = make_message();
    if constexpr (detail::has_string_sink_loc_v<logging_backend>) {
      logger().log(level::critical, msg, source_location::current());
    } else if constexpr (detail::has_string_sink_v<logging_backend>) {
      logger().log(level::critical, msg);
    }
#endif
  }
}

} // namespace trailblaze::log
