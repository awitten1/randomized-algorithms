#include "quicksort.h"
// #include "rand.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <benchmark/benchmark.h>

static void BM_Quicksort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = utils::uniform_int_vec(1000000);
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
  std::string x = "hello";
  for (auto _ : state) {
    state.PauseTiming();
    auto vec = utils::uniform_int_vec(1000000);
    state.ResumeTiming();
    std::sort(vec.begin(), vec.end());
  }
}
BENCHMARK(BM_StdSort);

BENCHMARK_MAIN();