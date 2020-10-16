#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

void print_vector(vector<int>& vec) {
  for (auto elem : vec) {
    cout << elem << " ";
  }
  cout << "\n";
}

class MergeSorter {
    void merge(vector<int>&, int, int, int);
    void merge_sort(vector<int>&, int, int);
  public:
    vector<int> result;
    void sort();
    MergeSorter(vector<int> start);
};

MergeSorter::MergeSorter(vector<int> start) {
  result = start;
  print_vector(result);
};

void MergeSorter::sort() {
  merge_sort(result, 0, result.size() - 1);
}

void MergeSorter::merge_sort(vector<int>& vec, int low_idx, int high_idx) {
  if (low_idx < high_idx) {
    int mid_idx = (low_idx + high_idx) / 2;
    merge_sort(vec, low_idx, mid_idx);
    merge_sort(vec, mid_idx + 1, high_idx);
    merge(vec, low_idx, mid_idx, high_idx);
  }
}

void MergeSorter::merge(vector<int>& vec, int low_idx, int mid_idx, int high_idx) {
  auto len_left = mid_idx - low_idx + 1;
  auto len_right = high_idx - mid_idx;

  vector<int> vec_left(len_left);
  vector<int> vec_right(len_right);

  for (auto i = 0; i < len_left; ++i) {
    vec_left.at(i) = vec.at(low_idx + i);
  }
  for (auto i = 0; i < len_right; ++i) {
    vec_right.at(i) = vec.at(i + mid_idx + 1);
  }

  vec_left.push_back(numeric_limits<int>::max());
  vec_right.push_back(numeric_limits<int>::max());

  int i = 0;
  int j = 0;
  for (auto k = low_idx; k <= high_idx; ++k) {
    if (vec_left.at(i) <= vec_right.at(j)) {
      vec.at(k) = vec_left.at(i);
      ++i;
    } else {
      vec.at(k) = vec_right.at(j);
      ++j;
    }
  }
}

int main(int argc, char** argv) {
  vector<int> unsorted;
  
  for (int i = 1; i < argc; ++i) {
    int int_arg = strtol(argv[i], nullptr, 0);
    unsorted.push_back(int_arg);
  }
  
  auto sorter = MergeSorter(unsorted);
  sorter.sort();
  print_vector(sorter.result);

  return 0;
}