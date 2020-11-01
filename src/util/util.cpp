#include <iostream>
#include "util.hpp"

using namespace std;
using namespace Util;

void print_vector(const vector<int>& vec) {
  for (auto elem : vec) {
    cout << elem << " ";
  }
  cout << "\n";
}

