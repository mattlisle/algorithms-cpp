#include "dp.hpp"
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
