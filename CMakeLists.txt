# ===========================================================================
#  CMake project setup
# ===========================================================================

cmake_minimum_required(VERSION 3.15)

# Provides the version from the version header
include(cmake/version.cmake)
parse_version()

project(trailblaze
  LANGUAGES C CXX
  VERSION ${trailblaze_VERSION}
)

# ---------------------------------------------------------------------------
#  Configuration
#   The project offers some configuration options that may be altered here.
#   In general those can be overwritten by cmake invokation with -D command
#   line options.
#
#   Example: -DENABLE_TESTING=off will overwrite the value configured here
#
# ---------------------------------------------------------------------------

option(ENABLE_INSTALL "Activates support for installing the project" ON)
option(ENABLE_TESTING "Activates support for unit tests" ON)
# If unit test support is ON: decide if you want provided or external GTest
option(USE_EXTERNAL_GTEST "Use preinstalled/externally provided GTest" OFF)
option(ENABLE_CCACHE "Enables CCache integration" ON)
option(ENABLE_CLANG_TIDY "Enables Clang-Tidy integration" ON)

# Set the project wide C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
#  Setup for clang-tidy
# ---------------------------------------------------------------------------

# CMake integration
find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
if(CLANG_TIDY_EXE)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR};-format-style=file")
endif()

# On demand pseudo target for manual runs
find_program(RUN_CLANG_TIDY NAMES run-clang-tidy run-clang-tidy.py)
if(RUN_CLANG_TIDY)
  add_custom_target(tidy
    COMMAND "${RUN_CLANG_TIDY}" -p "${CMAKE_BINARY_DIR}" -format-style=file
    COMMENT "Running clang-tidy over the whole project")
endif()

# ---------------------------------------------------------------------------
#  Setup for CTest / CCache / install dirs
# ---------------------------------------------------------------------------

# Install directories according to GNU standard
if(ENABLE_INSTALL)
  include(GNUInstallDirs)
endif()

# Unit testing
if(ENABLE_TESTING)
  include(CTest)
  if(USE_EXTERNAL_GTEST)
    # Prefer config package first; fall back to module if needed.
    find_package(GTest CONFIG QUIET)
    if(NOT GTest_FOUND)
      find_package(GTest REQUIRED) # module mode (FindGTest.cmake)
    endif()
  else()
    include(FetchContent)
    set(GTEST_TAG v1.17.0 CACHE STRING "googletest release tag")
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        ${GTEST_TAG}
      FIND_PACKAGE_ARGS NAMES GTest # allows FetchContent_MakeAvailable to prefer a preexisting package
    )
    # Either use an internal or external package
    FetchContent_MakeAvailable(googletest)
  endif()
  enable_testing()
endif()

# CCache integration
if(ENABLE_CCACHE)
  find_program(CCACHE_FOUND ccache REQUIRED)
  if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  endif()
endif()


# ---------------------------------------------------------------------------
#  Setup summary
# ---------------------------------------------------------------------------

message(STATUS "----------------------------------------------------------------------")
message(STATUS "Building ${CMAKE_PROJECT_NAME} in version ${CMAKE_PROJECT_VERSION}")
message(STATUS " C++ standard:       ${CMAKE_CXX_STANDARD}")
message(STATUS " Installing enabled: ${ENABLE_INSTALL}")
message(STATUS " Unit tests enabled: ${ENABLE_TESTING}")
message(STATUS " Use external GTest: ${USE_EXTERNAL_GTEST}")
message(STATUS " CCache enabled:     ${ENABLE_CCACHE}")
message(STATUS " Clang-Tidy enabled: ${ENABLE_CLANG_TIDY}")
message(STATUS "----------------------------------------------------------------------")


# ===========================================================================
#  Build targets
# ===========================================================================

add_library(trailblaze INTERFACE)

target_include_directories(trailblaze
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_executable(hello
  src/hello.cpp
)

list(APPEND INSTALL_TARGETS hello)

add_subdirectory(example)
# ===========================================================================
#  Unit tests
# ===========================================================================

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()


# ===========================================================================
#  Installation
# ===========================================================================

if(ENABLE_INSTALL)

  # Install targets and define the export targets.
  install(
    TARGETS ${INSTALL_TARGETS}
    EXPORT trailblazeTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  # Define the trailblazeTargets.cmake file and the namespace for exported targets.
  install(
    EXPORT trailblazeTargets
    FILE trailblazeTargets.cmake
    NAMESPACE trailblaze::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/trailblaze
  )

  include(CMakePackageConfigHelpers)
  # Generate a trailblazeConfigVersion.cmake file.
  # Preconfigured is a compatibility of 'SameMajorVersion'. Adjust this to your needs.
  # https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#generating-a-package-version-file
  write_basic_package_version_file(
    "trailblazeConfigVersion.cmake"
    VERSION ${trailblaze_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  # Install the config files.
  install(
    FILES
    "trailblazeConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/trailblazeConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/trailblaze
  )

endif()
