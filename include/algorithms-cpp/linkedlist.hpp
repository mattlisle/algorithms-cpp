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
    std::unique_ptr<Node> copy_all(Node* node) {
      if (node->next == nullptr) {
        auto node_copy {std::make_unique<Node>(node->elem)};
        return node_copy;
      } else {
        auto node_copy {std::make_unique<Node>(node->elem)};
        node_copy->next = copy_all(node->next);
        return node_copy;
      }
    };
    explicit Node(T elem) : elem{elem}, next{nullptr} {}
  };
  
  friend std::ostream& operator<<<>(std::ostream& strm, const Seq& seq);
  std::unique_ptr<Node> first;

public:
  Seq() noexcept { first = nullptr; }
  Seq(Seq& seq);
  Seq(Seq&& seq) noexcept;
  ~Seq() noexcept;
  T head();
  void prepend(const T& elem);
};

/*
@tailrec
def copySeq[T](subseq: Seq[T]) = subseq match {
  case Seq() => Seq()
  case Seq(elem) => Seq(elem)
  case Seq(elem, elems @ _*) = elem +: copySeq(elems)
}
*/
template<typename T>
Seq<T>::Seq(Seq& seq) {
  while (first != nullptr) {
    first = std::move(first->next);
  }
  auto* node_to_copy = seq.first.get();
  first = Seq<T>::Node::copy_all(node_to_copy);
}

template<typename T>
Seq<T>::Seq(Seq&& seq) noexcept {
  first = std::move(seq.first);
}

template<typename T>
Seq<T>::~Seq() noexcept {
  while (first != nullptr) {
    first = std::move(first->next);
  }
}

template<typename T>
T Seq<T>::head() {
  if (first == nullptr) {
    throw HeadOfEmptyCollection();
  } else {
    return first->elem;
  }
}

template<typename T>
void Seq<T>::prepend(const T& elem) {
  auto node{std::make_unique<Node>(elem)};
  node->next = std::move(first);
  this->first = std::move(node);
}

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