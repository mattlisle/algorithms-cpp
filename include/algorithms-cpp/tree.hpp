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
    explicit Node(const Key& key, const Val& value)
        : key {key}, value {value} {}
    Node() = default;
  };
  void transplant(const std::shared_ptr<Node>& prev,
                  std::shared_ptr<Node> next);
  [[nodiscard]] std::optional<std::shared_ptr<Node>> get_node(Key key) const;
  std::shared_ptr<Node> root;
  [[nodiscard]] static std::shared_ptr<Node>
  min(const std::shared_ptr<Node>& start);
  void foreach (const std::function<void(Key, Val)>& fn,
                const std::shared_ptr<Node>& node) const;
  void mappify(std::shared_ptr<std::map<size_t, Node>> nodes,
               std::shared_ptr<Node> node,
               size_t&& idx) const;
  friend std::ostream& operator<<(std::ostream& stream, const BinaryTree& tr);

public:
  BinaryTree(std::initializer_list<std::pair<Key, Val>> elems);

  /**
   * @brief Get the value associated with a key, if it exists
   *
   * @param key associated with the desired value
   * @return std::optional<Val> the value associated with the provided key
   */
  [[nodiscard]] std::optional<Val> get(Key key) const;

  /**
   * @brief Get the value associated with the next-largest key in the tree, if
   * it exists
   *
   * @param key reference element
   * @return std::optional<Val> value associated with the next-largest key
   */
  [[nodiscard]] std::optional<Val> successor(Key key) const;

  /**
   * @brief Get the value associated with the minimum key
   */
  [[nodiscard]] Val min() const;

  /**
   * @brief Get the value associated with the maximum key
   */
  [[nodiscard]] Val max() const;

  /**
   * @brief Get the number of nodes in the tree
   */
  [[nodiscard]] size_t size() const;

  /**
   * @brief Add the k-v pair to the tree, overwrite the value of the associated
   * key if it's already in the tree
   */
  void insert(Key key, Val val);

  /**
   * @brief Remove a k-v pair from the tree
   */
  void drop(Key key);

  /**
   * @brief Return true if the tree is empty
   */
  [[nodiscard]] bool empty() const { return root == nullptr; }

  /**
   * @brief Iterate over the tree and execute some function on each k-v pair
   *
   * @param fn function to apply to each k-v pair, but it cannot modify any
   * key/value
   */
  void foreach (const std::function<void(Key, Val)>& fn) const;
};

} // namespace tree

#endif // TREE_h