#include "sort.hpp"
#include <vector>

namespace sort {
namespace {

size_t partition(std::vector<int>* source, size_t start_idx, size_t end_idx) {
  auto pivot_elem = source->at(end_idx);
  size_t target_idx = start_idx - 1;
  for (auto i = start_idx; i < end_idx; ++i) {
    if (source->at(i) < pivot_elem) {
      ++target_idx;
      std::swap((*source)[target_idx], (*source)[i]);
    }
  }
  ++target_idx;
  std::swap((*source)[target_idx], (*source)[end_idx]);
  return target_idx;
}

void quick_sort_helper(std::vector<int>* source,
                       size_t start_idx,
                       size_t end_idx) {
  while (start_idx < end_idx) {
    auto mid_idx = partition(source, start_idx, end_idx);
    if (mid_idx > 0) {
      quick_sort_helper(source, start_idx, mid_idx - 1);
    }
    start_idx = mid_idx + 1;
  }
}
} // namespace

void quick_sort(std::vector<int>* source) {
  if (source->size() > 1) {
    quick_sort_helper(source, 0, source->size() - 1);
  }
}
} // namespace sort