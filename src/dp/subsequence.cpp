#include "dp.hpp"
#include "util.hpp"
#include <algorithm>

/*
  m i d d l e
f 0 0 0 0 0 0
i 0 1 1 1 1 1
d 0 1 2 2 2 2
d 0 1 2 3 3 3
l 0 1 2 3 4 4
e 0 1 2 3 4 5

  m a t t
g 0 0 0 0
n 0 0 0 0
a 0 1 0 0
t 0 1 2 2

  b d c a b a
a 0 0 0 1 1 1
b 1 1 1 1 2 2
c 1 1 2 2 2 2
b 1 1 2 2 3 3
d 1 2 2 2 3 3
a 1 2 2 3 3 4
b 1 2 2 3 4 4
*/

namespace dp {
namespace {

size_t DIAG = 0;
size_t LEFT = 1;
size_t UP = 2;

size_t solve_subproblems(const std::vector<int>& a,
                         const std::vector<int>& b,
                         util::Table* path_table) {
  util::Table length_table(a.size() + 1, b.size() + 1);
  for (size_t i = 1; i <= a.size(); ++i) {
    for (size_t j = 1; j <= b.size(); ++j) {
      auto left_len = length_table.at(i, j - 1);
      auto up_len = length_table.at(i - 1, j);
      if (a.at(i - 1) == b.at(j - 1)) {
        length_table.at(i, j) = length_table.at(i - 1, j - 1) + 1;
        path_table->at(i, j) = DIAG;
      } else if (left_len > up_len) {
        length_table.at(i, j) = left_len;
        path_table->at(i, j) = LEFT;
      } else {
        length_table.at(i, j) = up_len;
        path_table->at(i, j) = UP;
      }
    }
  }
  return length_table.at(a.size(), b.size());
}

void find_subsequence(std::vector<int>* subsequence,
                      const std::vector<int>& sequence,
                      util::Table* path_table) {
  size_t row = path_table->rows() - 1;
  size_t col = path_table->cols() - 1;
  size_t idx = subsequence->size() - 1;
  while (row != 0 && col != 0) {
    if (path_table->at(row, col) == DIAG) {
      subsequence->at(idx) = sequence.at(row - 1);
      --idx;
      --row;
      --col;
    } else if (path_table->at(row, col) == UP) {
      --row;
    } else {
      --col;
    }
  }
}
} // namespace

std::vector<int> longest_subsequence(const std::vector<int>& a,
                                     const std::vector<int>& b) {
  util::Table path_table(a.size() + 1, b.size() + 1);
  auto longest_length = solve_subproblems(a, b, &path_table);
  std::vector<int> subsequence(longest_length);
  find_subsequence(&subsequence, a, &path_table);
  return subsequence;
}

} // namespace dp