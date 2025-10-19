/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <cstdio>

#include "trailblaze/log/fmt_api.h"

int main() {
  // Nothing to initialize; the global() accessor will construct app::my_logger.
  // We selected the backend at compile time (see CMake/flags below).

  // fmt-style (preferred)
  ::trailblaze::log::log_info("hello {}", 42);

  // lazy fmt-style (avoids expensive arg evaluation when off)
  ::trailblaze::log::log_debug_lazy([&] { return fmt::format("expensive {}", 123); });

  // streaming (optional)
  ::trailblaze::log::log_stream(::trailblaze::log::level::warn) << "warn x=" << 3.14;

  return 0;
}
