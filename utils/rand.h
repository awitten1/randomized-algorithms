#pragma once

#include <random>
#include <vector>

namespace utils {

// mt19937 is super slow
template<typename T, typename Rand = std::minstd_rand>
auto uniform(T low, T high) {
  static Rand rng(std::random_device{}());
  std::uniform_int_distribution dist(low, high);
  return dist(rng);
}

inline std::vector<int> uniform_int_vec(int size) {
  std::vector<int> ret(size);
  std::generate(ret.begin(), ret.end(), []() { return uniform(0, 1000000); });
  return ret;
}

}