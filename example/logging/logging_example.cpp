/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#include <cmath>
#include <cstdio>

// Chose the API of your liking (include only one): FMT or stream API
#include "trailblaze/log/fmt_api.h"
#include "trailblaze/log/stream_api.h"

// Trailblaze supports different logging styles. The preferred one uses FMT-style string evaluation,
// but a streaming like API also exists.
//
// All functions demonstrated here exist for all log levels from trace up to critical.
//
// 1) FMT-style logging:
//    The functions for FMT-style logging look like this:
//       log_info("formatting", arg1, arg2, arg3);
//
//    In case evaluation of logging arguments is expensive, Trailblaze supports lazy-evaluation of
//    the logging parameters:
//        log_debug_lazy([&] { return fmt::format("expensive {}", 123); });
// 2) Streaming API:
//    In case you prefer to stream arguments, you can also use this API style:
//       log_stream<::trailblaze::log::level::warn>() << "warn x=" << 3.14;
//

// NOTE: The backend here is the @ref example::custom_logger that serves as an example on how to
// inject your own logging backend into Trailblaze. Also have a look at the CMakeLists.txt in this
// directory to see how the injection is done.

int main() {
  // Default: use FMT-style logging
  ::trailblaze::log::log_info("hello {}", 42);

  // For costly arg evaluation: use FMT-style logging with lazy-evaluation
  ::trailblaze::log::log_info_lazy([&] { return fmt::format("expensive {}", std::pow(123, 5)); });

  // streaming (optional)
  ::trailblaze::log::log_stream<::trailblaze::log::level::info>() << "x= " << 3.14;

  return 0;
}
