#include <iostream>
#include "util.hpp"

using namespace std;

namespace Util {

  /// Prints some vector to stdout
  void print_vector(const vector<int>& vec) {
    for (auto elem : vec) {
      cout << elem << " ";
    }
    cout << "\n";
  }

}  // namespace Util
