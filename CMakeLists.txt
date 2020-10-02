cmake_minimum_required(VERSION 3.15)
project(pyrodb)

include_directories(
  "include"
  "/usr/local/include"
  "/usr/local/opt/llvm/include"
  "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include"
  )
set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem ")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("INFO: Debug build")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("INFO: Release build")
elseif()
  message("WARNING: Unknown build type")
endif()

# set the headers
set(HEADERS
  include/pyrodb/container/hash/hash_function.hpp
  include/pyrodb/container/memory/bloom_filter.hpp
  include/pyrodb/container/memory/memtable.hpp
  include/pyrodb/db/db.hpp
  include/pyrodb/level/level.hpp
  include/pyrodb/run/run.hpp
  include/pyrodb/storage/sstable.hpp
  include/pyrodb/type/types.hpp
  include/pyrodb/util/util.hpp
)

# set sources
set(SOURCES
 src/container/memory/bloom_filer.cpp
 src/container/memory/memtable.cpp
 src/db/db.cpp
 src/level/level.cpp
 src/run/run.cpp
 src/storage/sstable.cpp
)


# add library
add_library(core ${HEADERS} ${SOURCES})

target_include_directories(core
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include)

target_compile_options(core PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 >
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic >
)

# add_executable(pyrodb-main
#   src/main.cpp
# )
# target_link_libraries(pyrodb-main PRIVATE core)


# build tests (targets: gtest_main, gtest)
enable_testing()
add_subdirectory(vendor/google/googletest)
add_subdirectory(test)

# build google benchmark (target: benchmark)
# do not build tests of benchmarking lib
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(vendor/google/benchmark)

# benches
add_executable(pyrodb-benchmark 
  bench/main.cpp
  bench/memory.cpp
)

target_link_libraries(pyrodb-benchmark PUBLIC
  benchmark
  core
)


