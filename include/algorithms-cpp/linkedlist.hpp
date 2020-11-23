#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>

namespace linkedlist {

class HeadOfEmptyList : std::exception {};

template <typename T>
class LinkedList;
template <typename T>
std::ostream& operator<<(std::ostream& strm, const LinkedList<T>& lst);

/**
 * @brief Basic implementation of a singly-linked list
 * 
 * Elements that are added are prepended, so insert and removal from the
 * start of the list can happen in constant time.
 * 
 * @tparam T type of element in the list
 */
template <typename T>
class LinkedList {
private:
  struct Node {
    T elem;
    std::unique_ptr<Node> next;
    explicit Node(T elem) : elem {elem}, next {nullptr} {}
  };

  std::unique_ptr<Node> first = nullptr;
  size_t size_ = 0;

  std::unique_ptr<Node> copy_nodes(Node* node);
  std::unique_ptr<Node> create_nodes(const T* begin, const T* end);
  friend std::ostream& operator<<<>(std::ostream& strm, const LinkedList& lst);

public:
  /**
   * @brief Construct a new Linked List object pre-filled with elements
   * 
   * @param elems elements provided in the initializer list
   */
  LinkedList(std::initializer_list<T> elems);

  /**
   * @brief Copy Linked List object
   * 
   * @param lst list to copy
   */
  LinkedList(LinkedList& lst);

  /**
   * @brief Move Linked List object
   * 
   * @param lst list to move
   */
  LinkedList(LinkedList&& lst) noexcept;

  /**
   * @brief Assign a copy of the provided list
   * 
   * @param lst list to copy
   */
  LinkedList& operator=(const LinkedList& lst);

  /**
   * @brief Move the provided list to another list object
   * 
   * @param lst list to move
   */
  LinkedList& operator=(LinkedList&& lst) noexcept;

  /**
   * @brief Destroy the Linked List object
   * 
   */
  ~LinkedList() noexcept;

  /**
   * @brief Get the first element of the list
   * @throw HeadOfEmptyList if the list itself is empty
   */
  T head();

  /**
   * @brief Get the first element of the list as an @ref std::optional<T>
   */
  std::optional<T> head_option();

  /**
   * @brief Find the element matching the provided condition, if any
   * 
   * @param comparator comparison that will be applied to each element in the list
   * @return std::optional<T> the matching element, if it exists
   */
  std::optional<T> find(std::function<bool(T)> comparator);

  /**
   * @brief Add an element to the start of the list in constant time
   * 
   * @param elem element to add
   */
  void prepend(const T& elem);

  /**
   * @brief Delete elements starting from the start of the list
   * 
   * @param n number of elements to delete, if greater than LinkedList::size(),
   *          the list will be left empty
   */
  void drop(size_t n) noexcept;
};

template <typename T>
std::unique_ptr<typename LinkedList<T>::Node>
LinkedList<T>::copy_nodes(Node* node) {
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
std::unique_ptr<typename LinkedList<T>::Node>
LinkedList<T>::create_nodes(const T* begin, const T* end) {
  if (begin == end) {
    return nullptr;
  } else {
    auto node {std::make_unique<Node>(*begin)};
    node->next = create_nodes(++begin, end);
    return node;
  }
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> elems) {
  first = create_nodes(elems.begin(), elems.end());
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList& lst) {
  while (first != nullptr) {
    first = std::move(first->next);
  }
  auto* node_to_copy = lst.first.get();
  first = LinkedList<T>::copy_nodes(node_to_copy);
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& lst) noexcept {
  first = std::move(lst.first);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& lst) {
  LinkedList<T> tmp(lst);
  std::swap(tmp);
  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& lst) noexcept {
  std::swap(lst);
  return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept {
  while (first != nullptr) {
    first = std::move(first->next);
  }
}

template <typename T>
T LinkedList<T>::head() {
  if (first == nullptr) {
    throw HeadOfEmptyList();
  } else {
    return first->elem;
  }
}

template <typename T>
std::optional<T> LinkedList<T>::head_option() {
  if (first == nullptr) {
    return std::nullopt;
  } else {
    return first->elem;
  }
}

template <typename T>
std::optional<T> LinkedList<T>::find(std::function<bool(T)> comparator) {
  auto* node = first.get();
  while (node != nullptr) {
    if (comparator(node->elem)) {
      return std::make_optional(node->elem);
    }
    node = node->next.get();
  }
  return std::nullopt;
}

template <typename T>
void LinkedList<T>::prepend(const T& elem) {
  auto node {std::make_unique<Node>(elem)};
  node->next = std::move(first);
  this->first = std::move(node);
  ++size_;
}

template <typename T>
void LinkedList<T>::drop(size_t n) noexcept {
  for (size_t i = 0; i < n ; ++i) {
    if (first == nullptr) {
      break;
    } else {
      first = std::move(first->next);
      --size_;
    }
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& strm,
                         const LinkedList<T>& lst) { // NOLINT
  auto* node = lst.first.get();
  strm << "LinkedList(";
  while (node != nullptr) {
    strm << node->elem;
    if (node->next != nullptr) {
      strm << ", ";
    }
    node = node->next.get();
  }
  strm << ')';
  return strm;
}
} // namespace linkedlist

#endif // LINKEDLIST_H