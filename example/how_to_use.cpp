#include "trailblaze/alg_resample.h"
#include "trailblaze/logging.h"
#include "trailblaze/path.h"
#include "trailblaze/space_se2.h"  // or space_se3.h / space_r2.h

void Example() {
  trailblaze::Path<trailblaze::SE2> p;
  // ... fill p ...

  std::vector<trailblaze::SE2> out;
  out.reserve(p.size() * 2);
  auto it = std::back_inserter(out);

  // Uses StateSpace<SE2> defaults (MetricXySe2 + InterpSe2Xy+Yaw):
  trailblaze::Resample<trailblaze::NullLogger>(p.states(), /*ds=*/0.1, it);

  // Or inject custom policies:
  trailblaze::Resample<trailblaze::NullLogger>(
      p.states(), 0.1, it, trailblaze::MetricXySe2{},         // where to place
      trailblaze::ComposeInterp<trailblaze::InterpSe2Xy>{});  // what to build
}
