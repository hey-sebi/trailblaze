/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
// external
#include <cstring>
#include <gtest/gtest.h>

#include "trailblaze/util.h"

namespace trailblaze {

TEST(Util, TestFindingPrefixes) {
  EXPECT_TRUE(starts_with("foobar", "foo"));
  EXPECT_TRUE(starts_with("foobar", "f"));
  EXPECT_TRUE(starts_with("foobar", "foobar"));
  EXPECT_TRUE(starts_with("foo/bar", "foo/"));
  EXPECT_FALSE(starts_with("foo/bar", "b"));
}

TEST(Util, TestTrimmingPrefixes) {
  struct test_pair {
    const char* raw;
    const char* prefix;
    const char* trimmed;
  };

  std::vector<test_pair> to_test = {
      {"foobar", "foo", "bar"},
      {"foobar", "foobar", ""},
      {"foobar", "baz", "foobar"},
      {"helloworld", "hel", "loworld"},
  };
  for (const auto& test : to_test) {
    const char* result = trim_prefix(test.raw, test.prefix);
    EXPECT_EQ(std::strcmp(result, test.trimmed), 0);
  }
}

} // namespace trailblaze
