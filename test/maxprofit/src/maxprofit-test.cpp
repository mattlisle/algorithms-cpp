#include "maxprofit.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <numeric>
#include <string>

using namespace std;

class MaxProfitTest : public ::testing::Test {
public:
  const vector<int> zero_elements{};
  const vector<int> one_element{1};
  const vector<int> positive_elements{10, 11, 7, 10, 6};
  const vector<int> negative_elements{-10, -1, -3, -5, -4};
  const vector<int> mixed_elements{
      13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  const vector<int> large_elements{numeric_limits<int>::max(),
                                   numeric_limits<int>::max()};

  void SetUp() override{

  };

  void TearDown() override{

  };

  static void test_planning(const vector<int>& vec,
                            const maxprofit::FinancialPlan& expected_plan) {
    maxprofit::FinancialPlan plan = maxprofit::create_plan(vec);
    ASSERT_EQ(plan.buy_idx, expected_plan.buy_idx);
    ASSERT_EQ(plan.sell_idx, expected_plan.sell_idx);
    ASSERT_EQ(plan.profit, expected_plan.profit);
  }
};

TEST_F(MaxProfitTest, max_profit_zero_elements) { // NOLINT
  maxprofit::FinancialPlan plan{0, 0, 0};
  test_planning(zero_elements, plan);
}

TEST_F(MaxProfitTest, max_profit_one_element) { // NOLINT
  maxprofit::FinancialPlan plan{0, 0, 1};
  test_planning(one_element, plan);
}

TEST_F(MaxProfitTest, max_profit_postive_elements) { // NOLINT
  int profit =
      accumulate(positive_elements.begin(), positive_elements.end(), 0);
  maxprofit::FinancialPlan plan{0, 4, profit};
  test_planning(positive_elements, plan);
}

TEST_F(MaxProfitTest, max_profit_negative_elements) { // NOLINT
  maxprofit::FinancialPlan plan{1, 1, -1};            // NOLINT
  test_planning(negative_elements, plan);
}

TEST_F(MaxProfitTest, max_profit_integer_elements) { // NOLINT
  maxprofit::FinancialPlan plan{7, 10, 43};          // NOLINT
  test_planning(mixed_elements, plan);
}

TEST_F(MaxProfitTest, max_profit_integer_limit_elements) { // NOLINT
  long profit = static_cast<long>(numeric_limits<int>::max()) +
                numeric_limits<int>::max();
  maxprofit::FinancialPlan plan{0, 1, profit};
  test_planning(large_elements, plan);
}
