#include "linkedlist.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <limits>
#include <numeric>
#include <string>

class LinkedListTest : public ::testing::Test {
public:
  void SetUp() override {

  };

  void TearDown() override {

  };
};

TEST_F(LinkedListTest, sandbox) { // NOLINT
  linkedlist::Seq<int> seq {};
  seq.prepend(1);
  std::cout << seq.head();
}
