include(FetchContent)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark
  GIT_TAG        v1.8.3
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(benchmark)