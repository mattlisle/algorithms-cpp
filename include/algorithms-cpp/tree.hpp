#ifndef TREE_H
#define TREE_H

#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace tree {

// Show the intention for being generic w/out effort of templatizing
using Key = int;
using Val = int;

/**
 * @brief Basic implementation of a binary search tree
 * 
 * Note: LinkedList was the mechanism I used to learn templates, so
 * I won't use them here to make this simpler.
 * 
 */
class BinaryTree {
private:
  struct Node {
    Key key {};
    Val value {};
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    explicit Node(const Key& key, const Val& value) : key {key}, value {value} {}
    Node() = default;
  };
  void transplant(const std::shared_ptr<Node>& prev, std::shared_ptr<Node> next);
  [[nodiscard]] std::optional<std::shared_ptr<Node>> get_node(Key key) const;
  std::shared_ptr<Node> root;
  [[nodiscard]] std::shared_ptr<Node> min(const std::shared_ptr<Node>& start) const;
  void foreach(const std::function<void(Key, Val)>& fn, const std::shared_ptr<Node>& node) const;
  void mappify(std::shared_ptr<std::map<size_t, Node>> nodes, std::shared_ptr<Node> node, size_t&& idx) const;
  friend std::ostream& operator<<(std::ostream& stream, const BinaryTree& tr);

public:
  [[nodiscard]] std::optional<Val> get(Key key) const;
  [[nodiscard]] std::optional<Val> successor(Key key) const;
  [[nodiscard]] Val min() const;
  [[nodiscard]] Val max() const;
  [[nodiscard]] size_t size() const;
  void insert(Key key, Val val);
  void drop(Key key);
  [[nodiscard]] bool empty() const { return root == nullptr; }
  void foreach(const std::function<void(Key, Val)>& fn) const;
};

} // namespace tree

#endif // TREE_h