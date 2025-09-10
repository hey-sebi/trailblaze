add_executable(generator_example
  generator_example.cpp
)

target_link_libraries(generator_example
  PRIVATE
  trailblaze
)