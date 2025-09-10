add_executable(matplotlib_example
  matplotlib_example.cpp
)

target_link_libraries(matplotlib_example
  PRIVATE
  trailblaze
)