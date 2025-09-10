#include <trailblaze/generate.h>
#include <trailblaze/path.h>
#include <trailblaze/sampling.h>

#include <iostream>

int main(int argc, char const* argv[])
{
  using trailblaze::Path;
  using trailblaze::R2;

  R2 start{1.0, 1.0};
  R2 goal{10.0, 8.0};
  trailblaze::sampling::ByCount policy;
  policy.n = 100;
  Path<R2> path_r2 = trailblaze::gen::LineR2(start, goal, policy);

  std::cout << "Path R2 with " << path_r2.size() << " states:\n" << path_r2 << std::endl;
  return 0;
}
