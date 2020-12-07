#include "dp.hpp"
#include "util.hpp"

namespace dp {

CutInstructions cut_rod(const std::vector<size_t>& prices_per_length) {
  std::vector<size_t> max_revenue_by_length(prices_per_length.size());
  std::vector<size_t> best_cuts(prices_per_length.size());
  for (size_t length = 1; length < prices_per_length.size(); length++) {
    size_t max_revenue_this_length = 0;
    for (size_t cut = 1; cut <= length; cut++) {
      size_t revenue_this_length =
          prices_per_length.at(cut) + max_revenue_by_length.at(length - cut);
      if (max_revenue_this_length < revenue_this_length) {
        max_revenue_this_length = revenue_this_length;
        best_cuts.at(length) = cut;
      }
    }
    max_revenue_by_length.at(length) = max_revenue_this_length;
  }
  std::vector<size_t> cut_lengths;
  auto length_left = prices_per_length.size() - 1;
  while (length_left > 0) {
    auto cut_length = best_cuts.at(length_left);
    cut_lengths.push_back(cut_length);
    length_left -= cut_length;
  }
  CutInstructions instructions {max_revenue_by_length.back(), cut_lengths};
  return instructions;
}

} // namespace dp
