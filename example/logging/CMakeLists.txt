add_executable(logging_example
  logging_example.cpp
)

# logging with trailblaze's fmt API:
target_compile_definitions(logging_example 
  PRIVATE 
  # Select the logging style
  TRAILBLAZE_WITH_FMT=1
)

target_link_libraries(logging_example 
  PRIVATE
  trailblaze
  fmt::fmt
)

target_include_directories(logging_example
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)


# Select the backend type at compile time:
target_compile_definitions(logging_example
  PRIVATE 
  # The header that contains the custom logger adapter
  TRAILBLAZE_LOG_BACKEND_HEADER=\"custom_logger.h\"
  # The fully qualified logger name 
  TRAILBLAZE_LOG_BACKEND=::app::custom_logger
)
