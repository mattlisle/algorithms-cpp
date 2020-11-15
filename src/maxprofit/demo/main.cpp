#include <iostream>
#include "maxprofit.hpp"
#include "util.hpp"
#include <vector>

using namespace std;
using namespace util;

auto main(int argc, char** argv) -> int {
  vector<int> history;
  string header = "Max Profit Demo";
  string usage = "./maxprofit-demo [numbers ...]";
  string description =
    "Imagines max-subarray problem as a max profit problem and "
    "finds best index to buy and sell given an array of integer daily 'stock price' changes";

  if (argc == 1) {
    print_usage(header, usage, description);
    exit(0);
  }

  try {
    for (int i = 1; i < argc; ++i) {
      int int_arg = stoi(argv[i], nullptr, 0); // NOLINT
      history.push_back(int_arg);
    }
  } catch (const exception& ex) {
    cout << "Invalid argument provided, see usage below:" << endl;
    print_usage(header, usage, description);
    exit(1);
  }

  maxprofit::FinancialPlan plan = maxprofit::create_plan(history);

  cout << "Buy at BOD: " << plan.buy_idx << endl;
  cout << "Sell at EOD: " << plan.sell_idx << endl;
  cout << "Profit: " << plan.profit << endl;
}