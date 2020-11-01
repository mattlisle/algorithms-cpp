#include <sort.hpp>
#include <limits>
#include <string>
#include "gtest/gtest.h"

using namespace std;

class MergeSortTest : public ::testing::Test {
  protected:
    vector<int> zero_element {};
    vector<int> one_element {1};
    vector<int> positive_elements {1, 5, 2, 9, 3};
    vector<int> negative_elements {-1, -3, -2, -8, -4};
    vector<int> mixed_elements {10, -20, -20, 40, -34, -100, 2};
    vector<int> large_elements {numeric_limits<int>::max(), 0, numeric_limits<int>::min()};

    virtual void SetUp() {

    };

    virtual void TearDown() {

    };

    virtual void test_sorting_of(vector<int> vec) {
      Sorter sorter {vec};
      auto result = sorter.merge_sort();
      EXPECT_EQ(result.size(), vec.size());

      stringstream message;
      message << "sorting failed on this subsequence: ";
      int prev = numeric_limits<int>::min();
      for (const auto& elem: result) {
        message << elem << " ";
        if (prev > elem) {
          FAIL() << message.str();
        } else {
          prev = elem;
        }
      }
    }
};

TEST_F(MergeSortTest, GivenZeroElements_Ok) {
  test_sorting_of(zero_element);
}

TEST_F(MergeSortTest, GivenOneElement_Ok) {
  test_sorting_of(one_element);
}

TEST_F(MergeSortTest, GivenPositiveElements_Ok) {
  test_sorting_of(positive_elements);
}

TEST_F(MergeSortTest, GivenNegativeElements_Ok) {
  test_sorting_of(negative_elements);
}

TEST_F(MergeSortTest, GivenMixedElements_Ok) {
  test_sorting_of(mixed_elements);
}

TEST_F(MergeSortTest, GivenLargeElements_Ok) {
  test_sorting_of(zero_element);
}