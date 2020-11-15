#ifndef CMAKE_SORT_H
#define CMAKE_SORT_H

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

/**
 * @brief Container for methods to sort a sequence of elements
 */
class Sorter {
  static void merge(std::vector<int> *vec_ptr,
                    size_t low_idx,
                    size_t mid_idx,
                    size_t high_idx);
  static void
  merge_sort_helper(std::vector<int> *vec_ptr, size_t low_idx, size_t high_idx);

public:
  /**
   * @brief Sort elements using merge sort
   *
   * @param source elements to sort
   * @return std::vector<int> sorted elements in vector form
   */
  static auto merge_sort(const std::vector<int> &source) -> std::vector<int>;
};

#endif // CMAKE_SORT_H
