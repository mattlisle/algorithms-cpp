#include <sort.hpp>

using namespace std;

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