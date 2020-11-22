#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <exception>
#include <forward_list>
#include <iostream>
#include <memory>

namespace linkedlist {

class HeadOfEmptyCollection : std::exception {};

template <typename T> class Seq;
template <typename T>
std::ostream& operator<<(std::ostream& strm, const Seq<T>& seq);

template <typename T> class Seq {
private:
  struct Node {
    T elem;
    std::unique_ptr<Node> next;
    explicit Node(T elem) : elem{elem}, next{nullptr} {}
  };
  friend std::ostream& operator<<<>(std::ostream& strm, const Seq& seq);
  std::unique_ptr<Node> first;

public:
  Seq() { first = nullptr; }
  ~Seq() {
    while (first != nullptr) {
      first = std::move(first->next);
    }
  }
  T head() {
    if (first == nullptr) {
      throw HeadOfEmptyCollection();
    } else {
      return first->elem;
    }
  }
  void prepend(const T& elem) {
    auto node{std::make_unique<Node>(elem)};
    node->next = std::move(first);
    this->first = std::move(node);
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& strm, const Seq<T>& seq) { // NOLINT
  auto* node = seq.first.get();
  strm << "Seq(";
  while (node != nullptr) {
    strm << node->elem;
    if (node->next != nullptr) {
      strm << ", ";
    } else {
      strm << ")";
    }
    node = node->next.get();
  }
  return strm;
}
} // namespace linkedlist

#endif // LINKEDLIST_H