#ifndef CMAKE_MAXPROFIT_H
#define CMAKE_MAXPROFIT_H

#include <vector>

namespace maxprofit {

class FinancialPlan {
public:
  const size_t buy_idx;
  const size_t sell_idx;
  const long profit;
  FinancialPlan(size_t buy, size_t sell, long prof)
      : buy_idx(buy), sell_idx(sell), profit(prof) {}
};

auto create_plan(const std::vector<int>& gain_loss_history) -> FinancialPlan;

} // namespace maxprofit

#endif // CMAKE_MAXPROFIT_H