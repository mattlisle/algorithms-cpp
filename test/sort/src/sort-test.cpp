#include "gtest/gtest.h"
#include <limits>
#include <sort.hpp>
#include <string>

using namespace std;

class SortTest : public ::testing::Test {
private:
  static void test_contents_match(const vector<int> &source,
                                  const vector<int> &result) {
    ASSERT_EQ(result.size(), source.size());
    map<int, set<int>> values_to_idxs;
    for (size_t i = 0; i < source.size(); ++i) {
      auto value = source[i];
      set<int> idxs{};
      if (values_to_idxs.find(value) != values_to_idxs.end()) {
        idxs = values_to_idxs[value];
      }
      idxs.insert(i);
      values_to_idxs[value] = idxs;
    }
    for (const auto &elem : result) {
      if (values_to_idxs.find(elem) != values_to_idxs.end()) {
        auto idxs = values_to_idxs[elem];
        ASSERT_FALSE(idxs.empty());
        idxs.erase(idxs.begin());
      } else {
        FAIL() << "Element in result not present in source: " << elem;
      }
    }
  }

public:
  const vector<int> zero_element{};
  const vector<int> one_element{1};
  const vector<int> positive_elements{1, 5, 2, 9, 3};
  const vector<int> negative_elements{-1, -3, -2, -8, -4};
  const vector<int> mixed_elements{10, -20, -20, 40, -34, -100, 2};
  const vector<int> large_elements{
      numeric_limits<int>::max(), 0, numeric_limits<int>::min()};

  void SetUp() override{

  };

  void TearDown() override{

  };

  static void test_sorting_of(const vector<int> &vec) {
    auto result = sort::merge_sort(vec);

    stringstream message;
    message << "sorting failed on this subsequence: ";
    int prev = numeric_limits<int>::min();
    for (const auto &elem : result) {
      message << elem << " ";
      if (prev > elem) {
        FAIL() << message.str();
      }
      prev = elem;
    }
  }
};

TEST_F(SortTest, merge_sort_zero_elements) { // NOLINT
  test_sorting_of(zero_element);
}

TEST_F(SortTest, merge_sort_one_element) { // NOLINT
  test_sorting_of(one_element);
}

TEST_F(SortTest, merge_sort_positive_elements) { // NOLINT
  test_sorting_of(positive_elements);
}

TEST_F(SortTest, merge_sort_negative_elements) { // NOLINT
  test_sorting_of(negative_elements);
}

TEST_F(SortTest, merge_sort_integer_elements) { // NOLINT
  test_sorting_of(mixed_elements);
}

TEST_F(SortTest, merge_sort_large_elements) { // NOLINT
  test_sorting_of(large_elements);
}