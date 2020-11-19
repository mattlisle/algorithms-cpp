#ifndef CMAKE_SORT_H
#define CMAKE_SORT_H

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace sort {

/**
 * @brief Sort elements using merge sort (not in-place)
 *
 * @param source elements to sort
 * @return std::vector<int> sorted elements in vector form
 */
void merge_sort(std::vector<int>* source);

/**
 * @brief Sort elements using heap sort (in-place)
 *
 * @param source_ptr elements to sort
 */
void heap_sort(std::vector<int>* source);

} // namespace sort

#endif // CMAKE_SORT_H
