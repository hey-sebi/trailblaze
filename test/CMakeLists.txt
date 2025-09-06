add_executable(example_test
  example_test.cpp
)

target_link_libraries(example_test
  PRIVATE
  GTest::gtest_main
  GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(example_test)
