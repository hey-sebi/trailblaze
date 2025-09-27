#include "trailblaze/alg_resample.h"
#include "trailblaze/logging.h"
#include "trailblaze/path.h"
#include "trailblaze/state_spaces/state_space_se2.h"

void Example()
{
  trailblaze::Path<trailblaze::StateSe2> path;
  // ... fill the path ...
  path.reserve(5);
  path.push_back({0., 0., 0.});
  path.push_back({1., 0., 0.});
  path.push_back({2., 0., 0.});
  path.push_back({3., 0., 0.});
  path.push_back({4., 0., 0.});

  std::vector<trailblaze::StateSe2> out;
  out.reserve(path.size() * 2);
  auto it = std::back_inserter(out);

  trailblaze::Resample<trailblaze::NullLogger>(path.states(), /*ds=*/0.1, it);
}

int main(int argc, char const* argv[])
{
  Example();
  return 0;
}
