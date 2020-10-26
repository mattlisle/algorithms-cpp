#include <sort.hpp>

using namespace std;

static const char* const HEADER = "\nSorting Demo\n\n";
static const char* const USAGE =
  "Usage:\n"
  "  ./sort-demo [numbers ...]\n\n"
  "Description:\n"
  "  Sorts the input array in ascending order\n";

int main(int argc, char** argv) {

  if (argc == 1) {
    cout << HEADER << USAGE;
    exit(0);
  }

  vector<int> unsorted;
  
  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0);
      unsorted.push_back(int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    cout << HEADER << USAGE;
    exit(1);
  }
  
  cout << "Input: ";
  print_vector(unsorted);

  auto sorter = MergeSorter(unsorted);
  sorter.sort();

  cout << "Output: ";
  print_vector(sorter.result);

  return 0;
}