#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <exception>
#include <iostream>
#include <memory>
#include <optional>

namespace linkedlist {

class HeadOfEmptyCollection : std::exception {};

template <typename T> class LinkedList;
template <typename T>
std::ostream& operator<<(std::ostream& strm, const LinkedList<T>& seq);

template <typename T> class LinkedList {
private:
  struct Node {
    T elem;
    std::unique_ptr<Node> next;
    explicit Node(T elem) : elem {elem}, next {nullptr} {}
  };

  std::unique_ptr<Node> first;

  std::unique_ptr<Node> copy_nodes(Node* node);
  std::unique_ptr<Node> create_nodes(const T* begin, const T* end);
  friend std::ostream& operator<<<>(std::ostream& strm, const LinkedList& seq);

public:
  LinkedList() noexcept { first = nullptr; }
  LinkedList(std::initializer_list<T> elems);
  LinkedList(LinkedList& seq);
  LinkedList(LinkedList&& seq) noexcept;
  LinkedList& operator=(const LinkedList& seq);
  LinkedList& operator=(LinkedList&& seq) noexcept;
  ~LinkedList() noexcept;
  T head();
  std::optional<T> head_option();
  std::optional<T> find(const T& elem);
  void prepend(const T& elem);
};

template <typename T>
std::unique_ptr<typename LinkedList<T>::Node> LinkedList<T>::copy_nodes(Node* node) {
  if (node->next == nullptr) {
    auto node_copy {std::make_unique<Node>(node->elem)};
    return node_copy;
  } else {
    auto node_copy {std::make_unique<Node>(node->elem)};
    node_copy->next = copy_nodes(node->next.get());
    return node_copy;
  }
};

template <typename T>
std::unique_ptr<typename LinkedList<T>::Node> LinkedList<T>::create_nodes(const T* begin,
                                                            const T* end) {
  if (begin == end) {
    return nullptr;
  } else {
    auto node {std::make_unique<Node>(*begin)};
    node->next = create_nodes(++begin, end);
    return node;
  }
}

template <typename T> LinkedList<T>::LinkedList(std::initializer_list<T> elems) {
  first = create_nodes(elems.begin(), elems.end());
}

template <typename T> LinkedList<T>::LinkedList(LinkedList& seq) {
  while (first != nullptr) {
    first = std::move(first->next);
  }
  auto* node_to_copy = seq.first.get();
  first = LinkedList<T>::copy_nodes(node_to_copy);
}

template <typename T> LinkedList<T>::LinkedList(LinkedList&& seq) noexcept {
  first = std::move(seq.first);
}

template <typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& seq) {
  LinkedList<T> tmp(seq);
  std::swap(tmp);
  return *this;
}

template <typename T> LinkedList<T>& LinkedList<T>::operator=(LinkedList&& seq) noexcept {
  std::swap(seq);
  return *this;
}

template <typename T> LinkedList<T>::~LinkedList() noexcept {
  while (first != nullptr) {
    first = std::move(first->next);
  }
}

template <typename T> T LinkedList<T>::head() {
  if (first == nullptr) {
    throw HeadOfEmptyCollection();
  } else {
    return first->elem;
  }
}

template <typename T> std::optional<T> LinkedList<T>::head_option() {
  if (first == nullptr) {
    return std::nullopt;
  } else {
    return first->elem;
  }
}

template <typename T> std::optional<T> LinkedList<T>::find(const T& elem) {
  auto* node = first.get();
  while (node != nullptr) {
    if (node->elem == elem) {
      return std::make_optional(elem);
    }
    node = node->next.get();
  }
  return std::nullopt;
}

template <typename T> void LinkedList<T>::prepend(const T& elem) {
  auto node {std::make_unique<Node>(elem)};
  node->next = std::move(first);
  this->first = std::move(node);
}

template <typename T>
std::ostream& operator<<(std::ostream& strm, const LinkedList<T>& seq) { // NOLINT
  auto* node = seq.first.get();
  strm << "LinkedList(";
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