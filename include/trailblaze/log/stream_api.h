/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <sstream>
#include <string>

#include "trailblaze/log/detail/detect.h"
#include "trailblaze/log/global.h"
#include "trailblaze/log/level.h"
#include "trailblaze/log/source_location.h"

namespace trailblaze::log {

/**
 * @brief No-op proxy returned when a level is disabled at compile time.
 *
 * All insertions are compiled away.
 */
struct null_stream_proxy {
  template <class T>
  constexpr const null_stream_proxy& operator<<(const T& /*unused*/) const noexcept {
    return *this;
  }
};

/**
 * @brief Streaming proxy that buffers to an ostringstream and flushes on destruction.
 *
 * Instantiated only when the requested level is compile-time enabled on the backend.
 * Flush sends the buffered message to the best available backend sink.
 *
 * @tparam B Selected backend type.
 */
template <class B>
class stream_proxy {
public:
  explicit stream_proxy(level lvl) : lvl_(lvl) {}
  stream_proxy(const stream_proxy&) = delete;
  stream_proxy(stream_proxy&&) = delete;
  stream_proxy& operator=(const stream_proxy&) = delete;
  stream_proxy& operator=(stream_proxy&&) = delete;

  template <class T>
  stream_proxy& operator<<(const T& t) {
    oss_ << t;
    return *this;
  }

  ~stream_proxy() noexcept {
    const std::string& message = buf_ = oss_.str();
    if constexpr (detail::has_string_sink_loc_v<B>) {
      logger().log(lvl_, message, source_location::current());
    } else if constexpr (detail::has_string_sink_v<B>) {
      logger().log(lvl_, message);
    } else {
      /* No compatible sink available: drop. */
    }
  }

private:
  level lvl_;
  std::ostringstream oss_;
  std::string buf_; /* ensures string_view lifetime if adapted later */
};

/**
 * @brief Begin a streaming log message for a given level.
 *
 * When the backend disables the level at compile time, returns a no-op proxy
 * whose operator<< is compiled out.
 */
inline auto log_stream(level lvl) {
  using logging_backend = ::trailblaze::log_config::backend;
  if constexpr (detail::level_enabled<logging_backend>(lvl)) {
    return stream_proxy<logging_backend>(lvl);
  } else {
    return null_stream_proxy{};
  }
}

} // namespace trailblaze::log
