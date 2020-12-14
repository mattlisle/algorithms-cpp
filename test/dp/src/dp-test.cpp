#include "dp.hpp"
#include "util.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <functional>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

class DpTest : public ::testing::Test {
public:
  const vector<size_t> prices {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  const vector<size_t> dimension_chain {30, 35, 15, 5, 10, 20, 25};

  void SetUp() override {

  };

  void TearDown() override {

  };
};

TEST_F(DpTest, cut_instructions) { // NOLINT
  auto instructions = dp::cut_rod(prices);
  ASSERT_THAT(instructions.cut_lengths, testing::ElementsAre(10));
  ASSERT_EQ(instructions.total_revenue, prices.back());
}

TEST_F(DpTest, table_functionality) { // NOLINT
  stringstream stream;
  dp::print_matrix_chain_order(stream, dimension_chain);
  ASSERT_EQ(stream.str(), "((M0(M1M2))((M3M4)M5))");
}
