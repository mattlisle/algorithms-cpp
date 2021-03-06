#include "tree.hpp"
#include "util.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char** argv) {

  string header = "Binary Search Tree Demo";
  string usage = "./tree-demo [numbers ...]";
  string description = "Constructs a tree and does stuff with it";

  if (argc == 1) {
    util::print_usage(header, usage, description);
    exit(0);
  }

  tree::BinaryTree bin_tree {};

  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
      bin_tree.insert(int_arg, int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    util::print_usage(header, usage, description);
    exit(1);
  }

  cout << bin_tree << endl;

  return 0;
}