#include "gtest/gtest.h"
#include <limits>
#include <sort.hpp>
#include <string>

using namespace std;

class MergeSortTest : public ::testing::Test {
  public:
    const vector<int> zero_element {};
    const vector<int> one_element {1};
    const vector<int> positive_elements {1, 5, 2, 9, 3};
    const vector<int> negative_elements {-1, -3, -2, -8, -4};
    const vector<int> mixed_elements {10, -20, -20, 40, -34, -100, 2};
    const vector<int> large_elements {numeric_limits<int>::max(), 0, numeric_limits<int>::min()};

    void SetUp() override {

    };

    void TearDown() override {

    };

    static void test_sorting_of(const vector<int>& vec) {
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
        }
        prev = elem;
      }
    }
};

TEST_F(MergeSortTest, GivenZeroElements_Ok) { // NOLINT
  test_sorting_of(zero_element);
}

TEST_F(MergeSortTest, GivenOneElement_Ok) { // NOLINT
  test_sorting_of(one_element);
}

TEST_F(MergeSortTest, GivenPositiveElements_Ok) { // NOLINT
  test_sorting_of(positive_elements);
}

TEST_F(MergeSortTest, GivenNegativeElements_Ok) { // NOLINT
  test_sorting_of(negative_elements);
}

TEST_F(MergeSortTest, GivenMixedElements_Ok) { // NOLINT
  test_sorting_of(mixed_elements);
}

TEST_F(MergeSortTest, GivenLargeElements_Ok) { // NOLINT
  test_sorting_of(large_elements);
}