#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <algorithm>
#include <exception>
#include <forward_list>
#include <vector>
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
  
  std::unique_ptr<Node> first;

  std::unique_ptr<Node> copy_nodes(Node* node);
  std::unique_ptr<Node> create_nodes(const T* begin, const T* end);
  friend std::ostream& operator<<<>(std::ostream& strm, const Seq& seq);

public:
  Seq() noexcept { first = nullptr; }
  Seq(std::initializer_list<T> elems);
  Seq(Seq& seq);
  Seq(Seq&& seq) noexcept;
  Seq& operator=(const Seq& seq);
  Seq& operator=(Seq&& seq) noexcept;
  ~Seq() noexcept;
  T head();
  void prepend(const T& elem);
};

template<typename T>
std::unique_ptr<typename Seq<T>::Node> Seq<T>::copy_nodes(Node* node)  {
  if (node->next == nullptr) {
    auto node_copy {std::make_unique<Node>(node->elem)};
    return node_copy;
  } else {
    auto node_copy {std::make_unique<Node>(node->elem)};
    node_copy->next = copy_nodes(node->next.get());
    return node_copy;
  }
};

template<typename T>
std::unique_ptr<typename Seq<T>::Node> Seq<T>::create_nodes(const T* begin, const T* end) {
  if (begin == end) {
    return nullptr;
  } else {
    auto node {std::make_unique<Node>(*begin)};
    node->next = create_nodes(++begin, end);
    return node;
  }
}

template<typename T>
Seq<T>::Seq(std::initializer_list<T> elems) {
  first = create_nodes(elems.begin(), elems.end());
}

template<typename T>
Seq<T>::Seq(Seq& seq) {
  while (first != nullptr) {
    first = std::move(first->next);
  }
  auto* node_to_copy = seq.first.get();
  first = Seq<T>::copy_nodes(node_to_copy);
}

template<typename T>
Seq<T>::Seq(Seq&& seq) noexcept {
  first = std::move(seq.first);
}

template<typename T>
Seq<T>& Seq<T>::operator=(const Seq<T>& seq) {
  Seq<T> tmp(seq);
  std::swap(tmp);
  return *this;
}

template<typename T>
Seq<T>& Seq<T>::operator=(Seq&& seq) noexcept {
  std::swap(seq);
  return *this;
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