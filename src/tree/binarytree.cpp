#include "tree.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <optional>

namespace tree {

void BinaryTree::transplant(const std::shared_ptr<BinaryTree::Node>& prev, std::shared_ptr<BinaryTree::Node> next) {
  if (next != nullptr) {
    next->parent = std::move(prev->parent);
  }
  if (prev->parent == nullptr) {
    root = std::move(next);
  } else if (prev->key == prev->parent->left->key) {
    prev->parent->left = std::move(next);
  } else {
    prev->parent->right = std::move(next);
  }
}

[[nodiscard]] std::optional<std::shared_ptr<BinaryTree::Node>> BinaryTree::get_node(Key key) const {
  auto node = root;
  while (node != nullptr && node->key != key) {
    node = key < node->key ? node->left : node->right;
  }
  if (node == nullptr) {
    return {};
  } else {
    return std::make_optional(node);
  }
}

[[nodiscard]] std::shared_ptr<BinaryTree::Node> BinaryTree::min(const std::shared_ptr<BinaryTree::Node>& start) const {
  if (start == nullptr) {
    throw std::exception();
  }
  auto node = start;
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

void BinaryTree::mappify(std::shared_ptr<std::map<size_t, BinaryTree::Node>> nodes, std::shared_ptr<BinaryTree::Node> node, size_t&& idx) const { // NOLINT
  if (node != nullptr) {
    (*nodes)[idx] = *node;
    mappify(nodes, node->left, 2 * idx + 1);
    mappify(nodes, node->right, 2 * idx + 2);
  }
}

[[nodiscard]] std::optional<Val> BinaryTree::get(Key key) const {
  auto node_opt = get_node(key);
  if (node_opt.has_value()) {
    return node_opt.value()->value;
  } else {
    return {};
  }
}

[[nodiscard]] std::optional<Val> BinaryTree::successor(Key key) const {
  auto node_opt = get_node(key);
  if (node_opt.has_value()) {
    auto node = std::move(node_opt.value());
    if (node->right == nullptr) {
      auto parent = node->parent;
      while (parent->parent != nullptr && node == parent->right) {
        auto tmp = parent->parent;
        node = std::move(parent);
        parent = std::move(tmp);
      }
      return parent->value;
    } else {
      return min(node)->value;
    }
  } else {
    return {};
  }
}

[[nodiscard]] Val BinaryTree::min() const {
  return min(root)->value;
}

[[nodiscard]] Val BinaryTree::max() const {
  auto node = root;
  while (node->right != nullptr) {
    node = node->right;
  }
  return node->value;
}

void BinaryTree::insert(Key key, Val val) {
  auto new_node = std::make_shared<BinaryTree::Node>(key, val);
  std::shared_ptr<BinaryTree::Node> parent = nullptr;
  auto child = root;
  while (child != nullptr) {
    parent = child;
    if (key < child->key) {
      child = child->left;
    } else {
      child = child->right;
    }
  }
  new_node->parent = parent;
  if (parent == nullptr) {
    root = std::move(new_node);
  } else if (key < parent->key) {
    parent->left = std::move(new_node);
  } else {
    parent->right = std::move(new_node);
  }
}

void BinaryTree::drop(Key key) {
  auto node_opt = get_node(key);
  if (node_opt.has_value()) {
    auto node = node_opt.value();
    if (node->left == nullptr) {
      transplant(node, node->right);
    } else if (node->right == nullptr) {
      transplant(node, node->left);
    } else {
      auto next_min_node = min(node->right);
      if (next_min_node->parent->key != node->key) {
        transplant(next_min_node, next_min_node->right);
        next_min_node->right = node->right;
        next_min_node->right->parent = next_min_node;
      }
      transplant(node, next_min_node);
      next_min_node->left = node->left;
      next_min_node->left->parent = next_min_node;
    }
  } else {
    throw std::exception();
  }
}

void BinaryTree::foreach(const std::function<void(Key, Val)>& fn, const std::shared_ptr<BinaryTree::Node>& node) const {
  if (node != nullptr) {
    fn(node->key, node->value);
    foreach(fn, node->left);
    foreach(fn, node->right);
  }
}

void BinaryTree::foreach(const std::function<void(Key, Val)>& fn) const {
  foreach(fn, root);
}

[[nodiscard]] size_t BinaryTree::size() const {
  size_t result {};
  auto fn = [&result](Key k __attribute__((__unused__)), Val v __attribute__((__unused__))) {result++;};
  foreach(fn);
  return result;
}

std::ostream& operator<<(std::ostream& stream, const BinaryTree& tr) {
  size_t n_nodes = tr.size();
  auto node_map = std::make_shared<std::map<size_t, BinaryTree::Node>>();
  tr.mappify(node_map, tr.root, 0);
  if (!node_map->empty()) {
    size_t height = ceil(log2(n_nodes));
    size_t width = pow(2, height);
    size_t checkpoint = 1;
    auto append_elem = [&stream,&node_map](size_t idx) {
      if (node_map->find(idx) != node_map->end()) {
        stream << node_map->at(idx).key;
      } else {
        stream << ' ';
      }
    };
    for (size_t idx = 0; idx <= node_map->rbegin()->first; ++idx) {
      append_elem(idx);
      if (idx + 1 == checkpoint) {
        stream << std::endl;
        checkpoint = 2 * checkpoint + 1;
      } else {
        stream << ',';
      }
    }
  }
  return stream;
}
} // namespace tree