#include "sort.hpp"
#include "util.hpp"

using namespace std;
using namespace util;

auto main(int argc, char** argv) -> int {

  string header = "Sorting Demo";
  string usage = "./sort-demo [numbers ...]";
  string description = "Sorts the input array in ascending order";

  if (argc == 1) {
    print_usage(header, usage, description);
    exit(0);
  }

  vector<int> source;

  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
      source.push_back(int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    print_usage(header, usage, description);
    exit(1);
  }

  cout << "Input: ";
  print_vector(source);

  sort::merge_sort(&source);

  cout << "Output: ";
  print_vector(source);

  return 0;
}