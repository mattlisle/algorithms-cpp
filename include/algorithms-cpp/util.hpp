#ifndef CMAKE_UTIL_H
#define CMAKE_UTIL_H

#include <algorithm>
#include <array>
#include <cmath>
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

class Table {
private:
  std::vector<size_t> elems;
  size_t rows_;
  size_t cols_;
  friend std::ostream& operator<<(std::ostream& strm, const Table& table);

public:
  Table(size_t rows, size_t cols)
      : rows_ {rows}, cols_ {cols}, elems(rows * cols) {};
  [[nodiscard]] size_t rows() const { return rows_; }
  [[nodiscard]] size_t cols() const { return cols_; }
  [[nodiscard]] size_t& at(size_t i, size_t j);
};

} // namespace util

#endif // CMAKE_UTIL_H
