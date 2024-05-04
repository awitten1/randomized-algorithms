#pragma once

#include <random>
#include <vector>

namespace utils {

namespace random {

struct SysRand {
  SysRand() {
    srand(std::random_device{}());
  }

  template<typename T>
  T operator()(T low, T high) {
    return (rand() % (high - low)) + low;
  }
};

struct MtRand {
  MtRand() : rng(std::random_device{}()) { }

  template<typename T>
  T operator()(T low, T high) {
    std::uniform_int_distribution dist(low, high);
    return dist(rng);
  }
private:
  std::mt19937 rng;
};

// mt19937 is super slow
template<typename T, typename Rand = SysRand>
auto uniform(T low, T high) {
  static Rand rng;
  return rng(low, high);
}

inline std::vector<int> uniform_int_vec(int size) {
  std::vector<int> ret(size);
  std::generate(ret.begin(), ret.end(), []() { return uniform(0, 1000000); });
  return ret;
}


}

}