#include "dp.hpp"
#include "util.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>

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

TEST_F(DpTest, longest_subsequence_functionality) { // NOLINT
  std::vector<int> a {0, 1, 2, 1, 3, 0, 1};
  std::vector<int> b {1, 3, 2, 0, 1, 0};
  auto subseq = dp::longest_subsequence(a, b);
  ASSERT_THAT(subseq, testing::ElementsAre(1, 2, 1, 0));
}
