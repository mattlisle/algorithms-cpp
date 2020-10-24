#ifndef CMAKE_SORT_H
#define CMAKE_SORT_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

void print_vector(vector<int>& vec);

class MergeSorter {
    void merge(vector<int>&, int, int, int);
    void merge_sort(vector<int>&, int, int);
  public:
    vector<int> result;
    void sort();
    MergeSorter(vector<int> start);
};

#endif // CMAKE_SORT_H
