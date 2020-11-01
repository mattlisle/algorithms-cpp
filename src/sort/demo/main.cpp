#include "sort.hpp"
#include "util.hpp"

using namespace std;

static const char* const HEADER = "\nSorting Demo\n\n";
static const char* const USAGE =
  "Usage:\n"
  "  ./sort-demo [numbers ...]\n\n"
  "Description:\n"
  "  Sorts the input array in ascending order\n";

auto main(int argc, char** argv) -> int {

  if (argc == 1) {
    cout << HEADER << USAGE;
    exit(0);
  }

  vector<int> unsorted;
  
  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
      unsorted.push_back(int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    cout << HEADER << USAGE;
    exit(1);
  }
  
  cout << "Input: ";
  Util::print_vector(unsorted);

  auto result = Sorter::merge_sort(unsorted);

  cout << "Output: ";
  Util::print_vector(result);

  return 0;
}