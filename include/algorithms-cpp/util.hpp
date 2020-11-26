#ifndef CMAKE_UTIL_H
#define CMAKE_UTIL_H

#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace util {

/// Prints a vector's contents to stdout
void print_vector(const std::vector<int>& vec);

template <typename T>
void print_vector(const std::vector<T>& vec) {
  for (auto elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

void print_usage(const std::string& header,
                 const std::string& usage,
                 const std::string& description);

} // namespace util

#endif // CMAKE_UTIL_H
