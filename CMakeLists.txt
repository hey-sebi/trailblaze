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
#   Example:
#     -DTRAILBLAZE_ENABLE_TESTING=off
#     will overwrite the value configured here
#
# ---------------------------------------------------------------------------

option(ENABLE_INSTALL "Activates support for installing the project" OFF)
option(TRAILBLAZE_ENABLE_TESTING "Activates support for unit tests" ON)
# If unit test support is ON: decide if you want provided or external GTest
option(TRAILBLAZE_USE_EXTERNAL_GTEST "Use preinstalled/externally provided GTest" OFF)
option(TRAILBLAZE_ENABLE_CCACHE "Enables CCache integration" ON)
option(TRAILBLAZE_ENABLE_CLANG_TIDY "Enables Clang-Tidy integration" OFF)
option(TRAILBLAZE_ENABLE_DOXYGEN "Enables doxygen documentation generation" ON)
option(TRAILBLAZE_WITH_FMT "Enable fmt-based logging API" ON)
option(TRAILBLAZE_USE_EXTERNAL_FMT "Use preinstalled/externally provided fmt" OFF)

# Set the project wide C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
#  Setup for clang-tidy
# ---------------------------------------------------------------------------

if (TRAILBLAZE_ENABLE_CLANG_TIDY)
  # CMake integration
  find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR};-format-style=file")
  endif()

#  # Custom target for manual runs.
#  find_program(RUN_CLANG_TIDY NAMES run-clang-tidy run-clang-tidy.py)
#  if(RUN_CLANG_TIDY)
#    file(GLOB_RECURSE TIDY_SOURCES
#      "${CMAKE_SOURCE_DIR}/example/*.cpp"
#      "${CMAKE_SOURCE_DIR}/test/*.cpp"
#    )
#    file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}" SRC_ROOT)
#    set(TIDY_HEADER_FILTER [=[^]=]${SRC_ROOT}[=[/(include|example|test)/]=])
#
#    add_custom_target(tidy
#      COMMAND "${RUN_CLANG_TIDY}"
#              -p "${CMAKE_BINARY_DIR}"
#              -style=file
#              -header-filter=${TIDY_HEADER_FILTER}
#              ${TIDY_SOURCES}
#      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
#      COMMENT "Running clang-tidy"
#    )
#  endif()
endif()

# ---------------------------------------------------------------------------
#  Setup for Doxygen
# ---------------------------------------------------------------------------

if(TRAILBLAZE_ENABLE_DOXYGEN)
  find_package(Doxygen REQUIRED)

  include(FetchContent)

  # Integrate doxygen-awesome theme
  FetchContent_Declare(
    doxygen_awesome
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG        v2.3.4
  )
  FetchContent_MakeAvailable(doxygen_awesome)

  # Paths for theme files
  set(DOXYGEN_AWESOME_DIR ${doxygen_awesome_SOURCE_DIR})

  # Configure Doxyfile from template
  set(DOXYGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/include")
  set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")
  set(DOXYGEN_PROJECT_NAME "trailblaze")
  set(DOXYGEN_PROJECT_BRIEF "A C++ library for modeling paths in robotics")

  configure_file(${CMAKE_SOURCE_DIR}/docs/Doxyfile.in
                 ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)

  #  Custom 'doc' target so we can generate the documentation with 'make doc' or 'ninja doc'
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )

endif()

# ---------------------------------------------------------------------------
#  Setup for CTest / CCache / install dirs
# ---------------------------------------------------------------------------

# Install directories according to GNU standard
if(ENABLE_INSTALL)
  include(GNUInstallDirs)
endif()

# Unit testing
if(TRAILBLAZE_ENABLE_TESTING)
  include(CTest)
  if(TRAILBLAZE_USE_EXTERNAL_GTEST)
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
if(TRAILBLAZE_ENABLE_CCACHE)
  find_program(CCACHE_FOUND ccache REQUIRED)
  if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  endif()
endif()

# ---------------------------------------------------------------------------
#  Setup for FMT
# ---------------------------------------------------------------------------
if (TRAILBLAZE_WITH_FMT)
  if (TRAILBLAZE_USE_SYSTEM_FMT)
    find_package(fmt REQUIRED)
  else()
    include(FetchContent)
    FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt.git
      GIT_TAG        11.0.2
      GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(fmt)
  endif()
endif()

# ---------------------------------------------------------------------------
#  Compiler settings
# ---------------------------------------------------------------------------

if (MSVC)
  add_compile_options(/W4 /permissive- /Zc:preprocessor /EHsc)
else()
  # By default we want the most strict settings to find all errors early on
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror )
  # Some exceptions
  add_compile_options(-Wno-unused-parameter)
endif()

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_UBSAN "Enable UBSanitizer" OFF)
if (ENABLE_ASAN AND NOT MSVC)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()
if (ENABLE_UBSAN AND NOT MSVC)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

# ---------------------------------------------------------------------------
#  Setup summary
# ---------------------------------------------------------------------------

message(STATUS "----------------------------------------------------------------------")
message(STATUS "Building ${CMAKE_PROJECT_NAME} in version ${CMAKE_PROJECT_VERSION}")
message(STATUS " C++ standard:       ${CMAKE_CXX_STANDARD}")
message(STATUS " Installing enabled: ${ENABLE_INSTALL}")
message(STATUS " Unit tests enabled: ${TRAILBLAZE_ENABLE_TESTING}")
message(STATUS " Use external GTest: ${TRAILBLAZE_USE_EXTERNAL_GTEST}")
message(STATUS " CCache enabled:     ${TRAILBLAZE_ENABLE_CCACHE}")
message(STATUS " Clang-Tidy enabled: ${TRAILBLAZE_ENABLE_CLANG_TIDY}")
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

target_compile_definitions(trailblaze
  INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES > # TODO: move to MSVC toolchain
  $<$<BOOL:${TRAILBLAZE_WITH_FMT}>:TRAILBLAZE_WITH_FMT=1>
  $<$<NOT:$<BOOL:${TRAILBLAZE_WITH_FMT}>>:TRAILBLAZE_WITH_FMT=0>
)

if (TRAILBLAZE_WITH_FMT)
  target_link_libraries(trailblaze
    INTERFACE
    fmt::fmt
  )
endif()

# list(APPEND INSTALL_TARGETS todo)

add_subdirectory(example)
# ===========================================================================
#  Unit tests
# ===========================================================================

if(TRAILBLAZE_ENABLE_TESTING)
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

  if(TRAILBLAZE_ENABLE_DOXYGEN)
    install(DIRECTORY "${DOXYGEN_OUTPUT_DIR}/html"
        DESTINATION "share/trailblaze/docs"
        OPTIONAL)
  endif()
endif()
