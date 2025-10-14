/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBLAZE_LOGGING_H_
#define TRAILBLAZE_LOGGING_H_

#include <initializer_list>
#include <ostream>

namespace trailblaze {

// Null logger: compiles away completely.
struct null_logger {
  static constexpr bool level_trace_enabled   = false;
  static constexpr bool level_debug_enabled   = false;
  static constexpr bool level_info_enabled    = false;
  static constexpr bool level_warning_enabled = false;
  static constexpr bool level_error_enabled   = false;

  template <typename... A>
  static void Trace(A&&...) noexcept {}

  template <typename... A>
  static void Debug(A&&...) noexcept {}

  template <typename... A>
  static void Info(A&&...) noexcept {}

  template <typename... A>
  static void Warn(A&&...) noexcept {}

  template <typename... A>
  static void Error(A&&...) noexcept {}
};

// Example adapter that writes to a provided ostream.
struct OstreamLogger {
  static constexpr bool level_trace_enabled   = true;
  static constexpr bool level_debug_enabled   = true;
  static constexpr bool level_info_enabled    = true;
  static constexpr bool level_warning_enabled = true;
  static constexpr bool level_error_enabled   = true;

  static void SetOut(std::ostream* os) {
    out_ = os;
  }

  template <typename... A>
  static void Trace(A&&... a) {
    (*out_) << "[  trace] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void Debug(A&&... a) {
    (*out_) << "[  debug] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void Info(A&&... a) {
    (*out_) << "[   info] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void Warn(A&&... a) {
    (*out_) << "[warning] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

  template <typename... A>
  static void Error(A&&... a) {
    (*out_) << "[  error] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

private:
  static std::ostream* out_;
};

inline std::ostream* OstreamLogger::out_ = nullptr;

// Compile-time elision of message construction.
#define TRAILBLAZE_LOG_DBG(Logger, EXPR_STREAM)                                                    \
  do {                                                                                             \
    if constexpr (Logger::level_debug_enabled) {                                                   \
      Logger::Debug EXPR_STREAM;                                                                   \
    }                                                                                              \
  } while (0)

} // namespace trailblaze

#endif
