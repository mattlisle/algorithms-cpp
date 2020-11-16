#ifndef CMAKE_SORT_H
#define CMAKE_SORT_H

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace sort {

/**
 * @brief Sort elements using merge sort
 *
 * @param source elements to sort
 * @return std::vector<int> sorted elements in vector form
 */
auto merge_sort(const std::vector<int>& source) -> std::vector<int>;

} // namespace sort

#endif // CMAKE_SORT_H
