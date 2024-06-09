#include "quicksort.h"

#if defined(__linux__)
#include "perf.h"
#endif

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <benchmark/benchmark.h>

static void BM_Quicksort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = utils::random::uniform_int_vec(1000000);

#if defined (__linux__)
    PerfEvents perf_events;
#endif

    state.ResumeTiming();
    quicksort(&vec);
    state.PauseTiming();
    if (!std::is_sorted(vec.begin(), vec.end())) {
      std::cerr << "Uh oh! Not sorted!" << std::endl;
      std::abort();
    }
    state.ResumeTiming();
  }
}
BENCHMARK(BM_Quicksort);

static void BM_StdSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = utils::random::uniform_int_vec(1000000);
    state.ResumeTiming();
    std::sort(vec.begin(), vec.end());
  }
}
BENCHMARK(BM_StdSort);

BENCHMARK_MAIN();