
add_executable(how_to_use
  how_to_use.cpp
)

target_link_libraries(how_to_use
  PRIVATE trailblaze
)

add_subdirectory(plot)