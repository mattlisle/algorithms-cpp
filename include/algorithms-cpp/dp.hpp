#ifndef DP_H
#define DP_H

#include <utility>
#include <vector>

namespace dp {

struct CutInstructions {
  size_t total_revenue;
  const std::vector<size_t> cut_lengths;
  CutInstructions(size_t total_revenue, std::vector<size_t> cut_lengths)
      : total_revenue {total_revenue}, cut_lengths {std::move(cut_lengths)} {};
};

CutInstructions cut_rod(const std::vector<size_t>& prices_per_length);

} // namespace dp

#endif // DP_H