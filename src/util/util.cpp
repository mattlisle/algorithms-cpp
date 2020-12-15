#include "util.hpp"

using namespace std;

namespace util {

/// Prints some vector to stdout
void print_vector(const vector<int>& vec) {
  for (auto elem : vec) {
    cout << elem << " ";
  }
  cout << "\n";
}

void print_usage(const std::string& header,
                 const std::string& usage,
                 const std::string& description) {
  cout << endl << header << endl << endl;
  cout << "Usage:" << endl;
  cout << "  " << usage << endl << endl;
  cout << "Description:" << endl;
  cout << "  " << description << endl;
}

size_t& Table::at(const size_t i, const size_t j) {
  return elems.at(i * cols_ + j);
}

std::ostream& operator<<(std::ostream& strm, const Table& table) {
  auto calc_digits = [](size_t el) {
    if (el == 0) {
      return static_cast<size_t>(1);
    } else {
      return static_cast<size_t>(floor(log10(static_cast<double>(el))) + 1);
    }
  };
  auto max_elem = *std::max_element(table.elems.begin(), table.elems.end());
  auto max_digits = calc_digits(max_elem);
  for (size_t i = 0; i < table.rows_; ++i) {
    for (size_t j = 0; j < table.cols_; j++) {
      auto elem = table.elems[i * table.cols_ + j];
      auto elem_digits = calc_digits(elem);
      for (auto k = elem_digits; k < max_digits; ++k) {
        strm << ' ';
      }
      strm << elem;
      if (j != table.cols_ - 1) {
        strm << ", ";
      }
    }
    strm << '\n';
  }
  return strm;
}

} // namespace util
