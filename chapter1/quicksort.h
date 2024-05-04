#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <iostream>

template<typename It>
static auto partition(It curr, It end) {
  int pivot = rand() % (end - curr - 1);
  std::swap(*(end - 1), *(curr + pivot));

  It begin_copy = curr;
  for (; curr != end; ++curr) {
    if (*curr < *(end - 1)) {
      std::swap(*curr, *(begin_copy++));
    }
  }

  std::swap(*begin_copy, *(end - 1));
  return begin_copy;
}

template<typename It>
static void quicksort(It begin, It end) {
  if (end - begin > 1) {
    auto it = partition(begin, end);
    quicksort(begin, it);
    quicksort(it + 1, end);
  }
}

template<typename T>
void quicksort(std::vector<T>* out) {
  quicksort(out->begin(), out->end());
}
