#include <trailblaze/generate.h>
#include <trailblaze/path.h>
#include <trailblaze/sampling.h>

#include <iostream>

int main(int argc, char const* argv[])
{
  using trailblaze::Path;
  using trailblaze::StateR2;

  StateR2 start{1.0, 1.0};
  StateR2 goal{10.0, 8.0};
  trailblaze::sampling::ByCount policy;
  policy.n = 100;
  Path<StateR2> path_r2 = trailblaze::gen::LineR2(start, goal, policy);

  std::cout << "Path StateR2 with " << path_r2.size() << " states:\n" << path_r2 << std::endl;
  return 0;
}
