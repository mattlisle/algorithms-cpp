#include "gtest/gtest.h"
#include "tree.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

class TreeTest : public ::testing::Test {
public:
  const vector<int> elements {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};

  void SetUp() override {

  };

  void TearDown() override {

  };
};

TEST_F(TreeTest, basic_test) { // NOLINT
  tree::BinaryTree bin_tree {};
  for (const auto& elem : elements) {
    bin_tree.insert(elem, elem);
  }
  ASSERT_EQ(2, bin_tree.min());
}
