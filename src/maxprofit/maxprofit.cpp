#include "maxprofit.hpp"
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

// printf("FinancialPlan(%d, %d, %d)\n", buy_idx, sell_idx, profit);
namespace maxprofit {
namespace {

auto find_max_crossing_period(const vector<int> &price_history,
                              size_t start_idx,
                              size_t mid_idx,
                              size_t end_idx) -> FinancialPlan {
  long neg_inf = numeric_limits<long>::min();
  long left_sum = neg_inf;
  long right_sum = neg_inf;
  size_t left_idx = 0;
  size_t right_idx = 0;
  long sum = 0;
  for (auto i = mid_idx; i != start_idx - 1; --i) {
    sum += price_history.at(i);
    if (sum > left_sum) {
      left_sum = sum;
      left_idx = i;
    }
  }
  sum = 0;
  for (size_t i = mid_idx + 1; i != end_idx + 1; ++i) {
    sum += price_history.at(i);
    if (sum > right_sum) {
      right_sum = sum;
      right_idx = i;
    }
  }

  long both_sum = 0;
  if (left_sum != neg_inf) {
    both_sum += left_sum;
  }
  if (right_sum != neg_inf) {
    both_sum += right_sum;
  }

  FinancialPlan plan{left_idx, right_idx, both_sum};
  return plan;
}

auto find_max_period(const vector<int> &price_history,
                     size_t start_idx,
                     size_t end_idx) -> FinancialPlan {
  if (price_history.empty()) {
    FinancialPlan plan{0, 0, 0};
    return plan;
  } else if (start_idx == end_idx) {
    FinancialPlan plan{start_idx, end_idx, price_history.at(start_idx)};
    return plan;
  } else {
    auto mid_idx = (start_idx + end_idx) / 2;
    FinancialPlan left_plan =
        find_max_period(price_history, start_idx, mid_idx);
    FinancialPlan right_plan =
        find_max_period(price_history, mid_idx + 1, end_idx);
    FinancialPlan cross_plan =
        find_max_crossing_period(price_history, start_idx, mid_idx, end_idx);

    if (left_plan.profit >= right_plan.profit &&
        left_plan.profit >= cross_plan.profit) {
      return left_plan;
    } else if (right_plan.profit >= left_plan.profit &&
               right_plan.profit >= cross_plan.profit) {
      return right_plan;
    } else {
      return cross_plan;
    }
  }
}

} // namespace

auto create_plan(const vector<int> &gain_loss_history) -> FinancialPlan {
  return find_max_period(gain_loss_history, 0, gain_loss_history.size() - 1);
}

} // namespace maxprofit
