#include <sort.hpp>
#include <utility>

using namespace std;

void print_vector(const vector<int>& vec) {
  for (auto elem : vec) {
    cout << elem << " ";
  }
  cout << "\n";
}

Sorter::Sorter(const vector<int>& source) {
  this->source = source;
};

auto Sorter::merge_sort() -> vector<int> {
  vector<int> result(source);
  if (!result.empty()) { 
    merge_sort_helper(&result, 0, result.size() - 1);
  }
  return result;
}

void Sorter::merge_sort_helper(vector<int>* vec_ptr, size_t low_idx, size_t high_idx) {
  if (low_idx < high_idx) {
    auto mid_idx = (low_idx + high_idx) / 2;
    merge_sort_helper(vec_ptr, low_idx, mid_idx);
    merge_sort_helper(vec_ptr, mid_idx + 1, high_idx);
    merge(vec_ptr, low_idx, mid_idx, high_idx);
  }
}

void Sorter::merge(vector<int>* vec_ptr, size_t low_idx, size_t mid_idx, size_t high_idx) {
  auto len_left = mid_idx - low_idx + 1;
  auto len_right = high_idx - mid_idx;

  vector<int> vec_left(len_left);
  vector<int> vec_right(len_right);

  for (auto i = 0; i < len_left; ++i) {
    vec_left.at(i) = vec_ptr->at(low_idx + i);
  }
  for (auto i = 0; i < len_right; ++i) {
    vec_right.at(i) = vec_ptr->at(i + mid_idx + 1);
  }

  vec_left.push_back(numeric_limits<int>::max());
  vec_right.push_back(numeric_limits<int>::max());

  int i = 0;
  int j = 0;
  for (auto k = low_idx; k <= high_idx; ++k) {
    if (vec_left.at(i) <= vec_right.at(j)) {
      vec_ptr->at(k) = vec_left.at(i);
      ++i;
    } else {
      vec_ptr->at(k) = vec_right.at(j);
      ++j;
    }
  }
}
