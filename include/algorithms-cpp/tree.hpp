#ifndef TREE_H
#define TREE_H

#include <functional>
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
  };
  void transplant(const std::shared_ptr<Node>& prev, std::shared_ptr<Node> next);
  std::optional<std::shared_ptr<Node>> get_node(Key key);
  std::shared_ptr<Node> root;
  std::shared_ptr<Node> min(const std::shared_ptr<Node>& start);

public:
  std::optional<Val> get(Key key);
  std::optional<Val> successor(Key key);
  Val min();
  Val max();
  void insert(Key key, Val val);
  void drop(Key key);
  bool empty() { return root == nullptr; }
  void foreach(std::function<void(Node)> fn);
};
} // namespace tree

#endif // TREE_h