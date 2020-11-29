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
  // const vector<int> elements {0, -2, 2, -3, -1, 1, 3, 4, 1};
  
  void SetUp() override {

  };

  void TearDown() override {

  };

  static void insert_elems(tree::BinaryTree* tr, const vector<int>& elems) {
    for (const auto& elem: elems) {
      tr->insert(elem, elem);
    }
  }
};

TEST_F(TreeTest, tree_construction) { // NOLINT
  tree::BinaryTree bin_tree {};
  insert_elems(&bin_tree, elements);
  ASSERT_EQ(2, bin_tree.min());
  ASSERT_EQ(20, bin_tree.max());
  ASSERT_EQ(11, bin_tree.size());
  bin_tree.foreach([&bin_tree](tree::Key k, tree::Key v) {
    ASSERT_EQ(v, bin_tree.get(k));
  });
  auto sorted_elems = elements;
  std::sort(sorted_elems.begin(), sorted_elems.end());
  for (size_t i = 0; i < sorted_elems.size() - 1; ++i) {
    ASSERT_EQ(sorted_elems.at(i + 1), bin_tree.successor(sorted_elems.at(i)));
  }
}

TEST_F(TreeTest, tree_insert_duplicate) { // NOLINT
  tree::BinaryTree bin_tree {};
  insert_elems(&bin_tree, elements);
  bin_tree.insert(2, 0);
  ASSERT_EQ(0, bin_tree.get(2).value());
  bin_tree.drop(2);
  ASSERT_EQ(nullopt, bin_tree.get(2));
}
