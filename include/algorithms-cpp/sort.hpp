#ifndef CMAKE_SORT_H
#define CMAKE_SORT_H

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

void print_vector(const std::vector<int>& vec);

class Sorter {
    static void merge(std::vector<int>* vec_ptr, size_t low_idx, size_t mid_idx, size_t high_idx);
    static void merge_sort_helper(std::vector<int>* vec_ptr, size_t low_idx, size_t high_idx);
    std::vector<int> source;
  public:
    auto merge_sort() -> std::vector<int>;
    explicit Sorter(const std::vector<int>& source);
};

#endif // CMAKE_SORT_H
