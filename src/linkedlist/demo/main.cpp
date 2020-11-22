
#include "linkedlist.hpp"
#include "util.hpp"
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

  linkedlist::Seq<int> seq {};

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

  linkedlist::Seq<int> seq_copy(seq);

  linkedlist::Seq<int> other_seq {0, 1, 2};

  cout << other_seq << endl;

  return 0;
}