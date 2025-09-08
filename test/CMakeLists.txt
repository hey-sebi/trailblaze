add_executable(test_state_spaces
  test_angle.cpp
  test_interpolation.cpp
  test_state_space_r2.cpp
  test_state_space_r3.cpp
  test_state_space_se2.cpp
  test_state_space_o3.cpp
)

target_link_libraries(test_state_spaces
  PRIVATE
  trailblaze
  GTest::gtest_main
  GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(test_state_spaces)
