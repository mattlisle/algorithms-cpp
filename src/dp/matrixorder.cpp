#include "dp.hpp"
#include "util.hpp"
#include <sstream>

namespace dp {
namespace {

void fill_chain_graph(util::Table* chain_graph,
                      const std::vector<size_t>& dims) {
  auto n_matrices = chain_graph->rows();
  util::Table cost_matrix(n_matrices, n_matrices);
  for (size_t chain_length = 2; chain_length <= n_matrices; ++chain_length) {
    for (size_t i = 0; i <= n_matrices - chain_length; ++i) {
      auto j = i + chain_length - 1;
      for (auto k = i; k < j; ++k) {
        auto q = cost_matrix.at(i, k) + cost_matrix.at(k + 1, j) +
                 dims.at(i) * dims.at(k + 1) * dims.at(j + 1);
        if (cost_matrix.at(i, j) == 0 || q < cost_matrix.at(i, j)) {
          cost_matrix.at(i, j) = q;
          chain_graph->at(i, j) = k;
        }
      }
    }
  }
}

void print_matrix_chain_order(std::stringstream& strm,
                              util::Table* chain_graph,
                              size_t i,
                              size_t j) {
  if (i == j) {
    strm << 'M' << i;
  } else {
    strm << '(';
    print_matrix_chain_order(strm, chain_graph, i, chain_graph->at(i, j));
    print_matrix_chain_order(strm, chain_graph, chain_graph->at(i, j) + 1, j);
    strm << ')';
  }
}
} // namespace

void print_matrix_chain_order(std::stringstream& strm,
                              const std::vector<size_t>& dimension_chain) {
  auto n_matrices = dimension_chain.size() - 1;
  util::Table chain_graph(n_matrices, n_matrices);
  fill_chain_graph(&chain_graph, dimension_chain);
  print_matrix_chain_order(strm, &chain_graph, 0, n_matrices - 1);
}

} // namespace dp