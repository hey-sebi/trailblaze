# Toolchain file for MSVC from VS20xx build tools with Ninja.
# Use with: cmake -G Ninja -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/msvc-ninja.cmake

# Tell CMake we're building for Windows with MSVC.
set(CMAKE_SYSTEM_NAME Windows)

# If you're in a VS20xx "Native Tools" prompt, cl.exe is already on PATH.
# These lines make the intent explicit and avoid CMake picking another compiler.
set(CMAKE_C_COMPILER   cl.exe)
set(CMAKE_CXX_COMPILER cl.exe)

# Default to 64-bit builds when in a generic shell.
# (Ignored if you already used the x64 Native Tools prompt.)
if(NOT DEFINED CMAKE_GENERATOR_PLATFORM)
  set(CMAKE_GENERATOR_PLATFORM x64 CACHE STRING "" FORCE)
endif()

# Choose MSVC runtime (CMake 3.15+).
# Change to MultiThreaded for /MT.
# Options:
#  MultiThreaded,
#  MultiThreadedDLL,
#  MultiThreadedDebug,
#  MultiThreadedDebugDLL
if(NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL") # /MD, /MDd in Debug automatically
endif()

# Reasonable MSVC defaults; keep warning level & Conformance mode on.
set(_COMMON_MSVC_FLAGS "/permissive- /W4 /EHsc /Zc:__cplusplus /Zc:preprocessor /Zc:externConstexpr /Zc:throwingNew")
# Maximum strictness:
# set(_COMMON_MSVC_FLAGS "/permissive- /Wall /WX /EHsc /Zc:__cplusplus /Zc:preprocessor /Zc:externConstexpr /Zc:throwingNew")

# Initialize flags for single-config generators like Ninja.
set(CMAKE_C_FLAGS_INIT          "${_COMMON_MSVC_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT        "${_COMMON_MSVC_FLAGS} /std:c++17")
set(CMAKE_RC_FLAGS_INIT         "")

# Typical build-type flags (only used by single-config generators).
# You can still use multi-config Ninja Multi-Config; adjust as needed.
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase") # /Zi + PDB
set(CMAKE_C_FLAGS_DEBUG_INIT          "/Zi /Od")
set(CMAKE_CXX_FLAGS_DEBUG_INIT        "/Zi /Od")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "/Zi /O2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "/Zi /O2 /DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT        "/O2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT      "/O2 /DNDEBUG")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT     "/O1 /DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT   "/O1 /DNDEBUG")

# Treat warnings as errors globally.
add_compile_options($<$<C_COMPILER_ID:MSVC>:/WX> $<$<CXX_COMPILER_ID:MSVC>:/WX>)
