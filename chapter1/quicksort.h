#pragma once

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>
#include "rand.h"

template<typename It>
static auto partition(It curr, It end) {
  using it_diff = std::iterator_traits<It>::difference_type;
  auto pivot = utils::random::uniform<it_diff>(0, end - curr - 1);
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

// How many comparisons executed for quicksort?
//
// Take two random elements: the ith and jth smallest.
// What is the probability the are compared?  If any element in between
// them is picked as the pivot before on of the two are picked,
// then the two elements are split up and never compared.
//
// If either of those two elements are picked as pivot first, then they are compared.
// The probability that one of those two elements is picked before anything in between them
// is 2 / (j - i + 1).
//
// Xij - 1 if elements i and j are compared, 0 otherwise
// total comparisons = E[sum_{i < j} Xij] = sum_{i < j} E[Xij] = 2 * sum_{i < j} 1 / (j - i + 1)
//                   = 2 * sum_{i = 1}^n sum_{j = i + 1}^n 1 / (j - i + 1)
//                   = 2 * sum_{i = 1}^n sum_{j = 2}^(n - i + 1) 1 / k
//                   <=  2 * sum_{i = 1}^n sum_{j = 1}^n 1 / j <= 2nlog(n)
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
