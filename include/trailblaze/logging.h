/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once
#include <initializer_list>
#include <ostream>

namespace trailblaze {

// Null logger: compiles away completely.
struct null_logger {
  static constexpr bool level_trace_enabled = false;
  static constexpr bool level_debug_enabled = false;
  static constexpr bool level_info_enabled = false;
  static constexpr bool level_warning_enabled = false;
  static constexpr bool level_error_enabled = false;

  template <typename... A>
  static void trace(A&&...) noexcept {}

  template <typename... A>
  static void debug(A&&...) noexcept {}

  template <typename... A>
  static void info(A&&...) noexcept {}

  template <typename... A>
  static void warn(A&&...) noexcept {}

  template <typename... A>
  static void error(A&&...) noexcept {}
};

// Example adapter that writes to a provided ostream.
class ostream_logger {
  static constexpr bool level_trace_enabled = true;
  static constexpr bool level_debug_enabled = true;
  static constexpr bool level_info_enabled = true;
  static constexpr bool level_warning_enabled = true;
  static constexpr bool level_error_enabled = true;

  static void set_out(std::ostream* os) {
    out_ = os;
  }

  template <typename... A>
  static void trace(A&&... a) {
    (*out_) << "[  trace] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void debug(A&&... a) {
    (*out_) << "[  debug] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void info(A&&... a) {
    (*out_) << "[   info] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void warn(A&&... a) {
    (*out_) << "[warning] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void error(A&&... a) {
    (*out_) << "[  error] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

private:
  /// The output stream that is logged to
  static std::ostream* out_;
};

inline std::ostream* ostream_logger::out_ = nullptr;

// Compile-time elision of message construction.
#define TRAILBLAZE_LOG_DBG(logger, EXPR_STREAM)                                                    \
  do {                                                                                             \
    if constexpr (logger::level_debug_enabled) {                                                   \
      logger::debug EXPR_STREAM;                                                                   \
    }                                                                                              \
  } while (0)

} // namespace trailblaze
