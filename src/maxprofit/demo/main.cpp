#include <iostream>
#include "maxprofit.hpp"
#include <vector>

using namespace std;

auto main(int argc, char** argv) -> int {
  vector<int> history;

  for (int i = 1; i < argc; ++i) {
    int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
    history.push_back(int_arg);
  }

  maxprofit::FinancialPlan plan = maxprofit::create_plan(history);

  cout << "But at index: " << plan.buy_idx << endl;
  cout << "Sell at index: " << plan.sell_idx << endl;
  cout << "Profit: " << plan.profit << endl;
}