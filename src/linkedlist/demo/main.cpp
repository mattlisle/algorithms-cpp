
#include "linkedlist.hpp"
#include "util.hpp"
#include <optional>
#include <string>

using namespace std;
using namespace util;

auto main(int argc, char** argv) -> int {

  string header = "Linked List Demo";
  string usage = "./linkedlist-demo [numbers ...]";
  string description = "Constructs a linked list and prints it";

  if (argc == 1) {
    print_usage(header, usage, description);
    exit(0);
  }

  linkedlist::LinkedList<int> seq {};

  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
      seq.prepend(int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    print_usage(header, usage, description);
    exit(1);
  }

  linkedlist::LinkedList<int> seq_copy(seq);

  linkedlist::LinkedList<int> other_seq {0, 1, 2};

  optional<int> maybe_elem = other_seq.find([](int elem) { return elem == 1; });

  int h = other_seq.head();
  h = -1;

  other_seq.drop(1);

  cout << maybe_elem.value() << endl;

  return 0;
}