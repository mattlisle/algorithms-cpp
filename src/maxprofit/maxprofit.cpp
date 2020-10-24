#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

using namespace std;

class FinancialPlan {
  public:
    int buy_idx;
    int sell_idx;
    int profit;
    FinancialPlan(int buy, int sell, int prof) : buy_idx(buy), sell_idx(sell), profit(prof) {}
    void print() {
      printf("FinancialPlan(%d, %d, %d)\n", buy_idx, sell_idx, profit);
    }
};

class FinancialPlanner {
  private:
    vector<int> price_history;
    FinancialPlan find_max_crossing_period(int, int, int);
    FinancialPlan find_max_period(int, int);
  public:
    FinancialPlan create_plan();
    FinancialPlanner(vector<int> history) : price_history(history) {}
};

FinancialPlan FinancialPlanner::find_max_crossing_period(int start_idx, int mid_idx, int end_idx) {
  int neg_inf = numeric_limits<int>::min();
  int left_sum = neg_inf;
  int right_sum = neg_inf;
  int left_idx;
  int right_idx;
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
  if (left_sum != neg_inf) both_sum += left_sum;
  if (right_sum != neg_inf) both_sum += right_sum;

  FinancialPlan plan(left_idx, right_idx, both_sum);
  return plan;
}

FinancialPlan FinancialPlanner::find_max_period(int start_idx, int end_idx) {
  if (start_idx == end_idx) {
    FinancialPlan plan(start_idx, end_idx, price_history[start_idx]);
    return plan;
  } else {
    auto mid_idx = (start_idx + end_idx) / 2;
    FinancialPlan left_plan = find_max_period(start_idx, mid_idx);
    FinancialPlan right_plan = find_max_period(mid_idx + 1, end_idx);
    FinancialPlan cross_plan = find_max_crossing_period(start_idx, mid_idx, end_idx);

    if (left_plan.profit >= right_plan.profit && left_plan.profit >= cross_plan.profit) {
      return left_plan;
    } else if (right_plan.profit >= left_plan.profit && right_plan.profit >= cross_plan.profit) {
      return right_plan;
    } else {
      return cross_plan;
    }
  }
}

FinancialPlan FinancialPlanner::create_plan() {
  return find_max_period(0, price_history.size());
}

int main(int argc, char** argv) {
  vector<int> history;

  for (int i = 1; i < argc; ++i) {
    int int_arg = strtol(argv[i], nullptr, 0);
    history.push_back(int_arg);
  }

  FinancialPlanner planner(history);
  FinancialPlan plan = planner.create_plan();

  printf("But at index: %d\nSell at index: %d\nProfit: %d\n", plan.buy_idx, plan.sell_idx, plan.profit);
  
}