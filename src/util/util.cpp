#include "util.hpp"
#include <iostream>

using namespace std;

namespace util {

/// Prints some vector to stdout
void print_vector(const vector<int> &vec) {
  for (auto elem : vec) {
    cout << elem << " ";
  }
  cout << "\n";
}

void print_usage(const std::string &header,
                 const std::string &usage,
                 const std::string &description) {
  cout << endl << header << endl << endl;
  cout << "Usage:" << endl;
  cout << "  " << usage << endl << endl;
  cout << "Description:" << endl;
  cout << "  " << description << endl;
}

} // namespace util
