#include "tree.hpp"
#include "util.hpp"
#include <iostream>
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

std::optional<std::shared_ptr<BinaryTree::Node>> BinaryTree::get_node(Key key) {
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

std::shared_ptr<BinaryTree::Node> BinaryTree::min(const std::shared_ptr<BinaryTree::Node>& start) {
  if (start == nullptr) {
    throw std::exception();
  }
  auto node = start;
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

std::optional<Val> BinaryTree::get(Key key) {
  auto node_opt = get_node(key);
  if (node_opt.has_value()) {
    return node_opt.value()->value;
  } else {
    return {};
  }
}

std::optional<Val> BinaryTree::successor(Key key) {
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

Val BinaryTree::min() {
  return min(root)->value;
}

Val BinaryTree::max() {
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

void foreach(std::function<void(Node)> fn) {
  
}
} // namespace tree