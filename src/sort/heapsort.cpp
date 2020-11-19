#include "sort.hpp"
#include <vector>

using namespace std;

namespace sort {
namespace {

auto parent_idx(size_t idx) -> size_t { return (idx - 1) / 2; }

auto left_idx(size_t idx) -> size_t { return 2 * idx + 1; }

auto right_idx(size_t idx) -> size_t { return 2 * idx + 2; }

void emplace_heap_elem(vector<int>* source, size_t heap_size, size_t idx) {
  auto left = left_idx(idx);
  auto right = right_idx(idx);
  auto largest = idx;
  if (left <= heap_size && source->at(left) > source->at(largest)) {
    largest = left;
  }
  if (right <= heap_size && source->at(right) > source->at(largest)) {
    largest = right;
  }
  if (largest != idx) {
    swap((*source)[idx], (*source)[largest]);
    emplace_heap_elem(source, heap_size, largest);
  }
}

void build_max_heap(vector<int>* source, size_t heap_size) {
  for (auto i = heap_size / 2; i-- > 0;) {
    emplace_heap_elem(source, heap_size, i);
  }
}

} // namespace

void heap_sort(vector<int>* source) {
  if (source->size() > 1) {
    auto heap_size = source->size() - 1;
    build_max_heap(source, heap_size);
    for (auto i = source->size() - 1; i > 0; --i) {
      swap((*source)[0], (*source)[i]);
      --heap_size;
      emplace_heap_elem(source, heap_size, 0);
    }
  }
}
} // namespace sort