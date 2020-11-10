#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include "maxprofit.hpp"

using namespace std;

// printf("FinancialPlan(%d, %d, %d)\n", buy_idx, sell_idx, profit);
namespace maxprofit {
namespace {

auto find_max_crossing_period(const vector<int>& price_history, int start_idx, int mid_idx, int end_idx) -> FinancialPlan {
  int neg_inf = numeric_limits<int>::min();
  int left_sum = neg_inf;
  int right_sum = neg_inf;
  int left_idx = 0;
  int right_idx = 0;
  int sum = 0;
  for (int i = mid_idx; i >= start_idx; --i) {
    sum += price_history[i];
    if (sum > left_sum) {
      left_sum = sum;
      left_idx = i;
    }
  }
  sum = 0;
  for (int i = mid_idx + 1; i <= end_idx; ++i) {
    sum += price_history[i];
    if (sum > right_sum) {
      right_sum = sum;
      right_idx = i;
    }
  }

  int both_sum = 0;
  if (left_sum != neg_inf) {
    both_sum += left_sum;
  }
  if (right_sum != neg_inf) {
    both_sum += right_sum;
  }

  FinancialPlan plan {left_idx, right_idx, both_sum};
  return plan;
}

auto find_max_period(const vector<int>& price_history, int start_idx, int end_idx) -> FinancialPlan {
  if (start_idx == end_idx) {
    FinancialPlan plan(start_idx, end_idx, price_history[start_idx]);
    return plan;
  } else {
    auto mid_idx = (start_idx + end_idx) / 2;
    FinancialPlan left_plan = find_max_period(price_history, start_idx, mid_idx);
    FinancialPlan right_plan = find_max_period(price_history, mid_idx + 1, end_idx);
    FinancialPlan cross_plan = find_max_crossing_period(price_history, start_idx, mid_idx, end_idx);

    if (left_plan.profit >= right_plan.profit && left_plan.profit >= cross_plan.profit) {
      return left_plan;
    } else if (right_plan.profit >= left_plan.profit && right_plan.profit >= cross_plan.profit) {
      return right_plan;
    } else {
      return cross_plan;
    }
  }
}

}  // namespace

auto create_plan(const vector<int>& price_history) -> FinancialPlan {
  return find_max_period(price_history, 0, price_history.size());
}

}  // namespace maxprofit
