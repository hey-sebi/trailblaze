#ifndef TRAILBLAZE_LOGGING_H_
#define TRAILBLAZE_LOGGING_H_

#include <initializer_list>
#include <ostream>

namespace trailblaze {

// Null logger: compiles away completely.
struct NullLogger {
  static constexpr bool kEnabledTrace = false;
  static constexpr bool kEnabledDebug = false;
  static constexpr bool kEnabledInfo = false;
  static constexpr bool kEnabledWarn = false;
  static constexpr bool kEnabledError = false;

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
  static constexpr bool kEnabledTrace = true;
  static constexpr bool kEnabledDebug = true;
  static constexpr bool kEnabledInfo = true;
  static constexpr bool kEnabledWarn = true;
  static constexpr bool kEnabledError = true;

  static void SetOut(std::ostream* os) { out_ = os; }

  template <typename... A>
  static void Debug(A&&... a) {
    (*out_) << "[DBG] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void Info(A&&... a) {
    (*out_) << "[INF] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void Warn(A&&... a) {
    (*out_) << "[WRN] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void Error(A&&... a) {
    (*out_) << "[ERR] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }
  template <typename... A>
  static void Trace(A&&... a) {
    (*out_) << "[TRC] ";
    (void)std::initializer_list<int>{(int((*out_) << a), 0)...};
    (*out_) << '\n';
  }

 private:
  static std::ostream* out_;
};

inline std::ostream* OstreamLogger::out_ = nullptr;

// Zero-cost compile-time elision of message construction.
#define TRAILBLAZE_LOG_DBG(Logger, EXPR_STREAM)     \
  do {                                        \
    if constexpr (Logger::kEnabledDebug) {    \
      Logger::Debug EXPR_STREAM;              \
    }                                         \
  } while (0)

}  // namespace trailblaze

#endif  // TRAILBLAZE_LOGGING_H_
