#include "AABBTreeNode.h"
#include <iostream>
#include <stack>

Node::Node(const AABB_box bbox) {
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  box = bbox;
  height = 0;
}

Node::Node(ptr &left, ptr &right) {

  this->box = Combine(left->box, right->box);
  left->parent = right->parent = this;
  this->height = std::max(left->height, right->height) + 1;
  this->parent = nullptr;
  this->left = std::move(left);
  this->right = std::move(right);
}

void Node::treeTraverse() {

  if (this->isLeaf()) {
    std::cout << "########leaf##########" << std::endl;
    std::cout << this->box.x() << std::endl;
    std::cout << this->box.y() << std::endl;
    std::cout << this->box.z() << std::endl;
    return;
  }
  std::cout << "#######node###########" << std::endl;
  std::cout << this->box.x() << std::endl;
  std::cout << this->box.y() << std::endl;
  std::cout << this->box.z() << std::endl;
  this->left->treeTraverse();
  this->right->treeTraverse();
}

bool Node::isLeaf() {

  if (!right)
    return true;

  return false;
}

void Node::insertLeaf(ptr &leaf) {
  auto curr = this;
  bool direction = 0;
  ptr newNode;
  AABB_box leaf_box = leaf->box;

  while (!curr->isLeaf()) {

    std::cout << Combine(this->left->box, leaf->box).getSurface() << "  "
              << Combine(this->right->box, leaf->box).getSurface() << std::endl;
    if (Combine(this->left->box, leaf->box).getSurface() >
        Combine(this->right->box, leaf->box).getSurface()) {
      curr = curr->right.get();
      direction = 1;
    } else {
      curr = curr->left.get();
      direction = 0;
    }
  }

  auto currParent = curr->parent;

  if (!direction) {
    newNode = std::make_unique<Node>(curr->parent->left, leaf);
    newNode->parent = currParent;
    currParent->left = std::move(newNode);

  }

  else {

    newNode = std::make_unique<Node>(curr->parent->right, leaf);
    newNode->parent = currParent;
    currParent->right = std::move(newNode);
  }
  curr = currParent;

  while (curr != nullptr) {

    curr->box = Combine(curr->box, leaf_box);
    curr->height++;
    curr = curr->parent;
  }
}

void Node::mergeTree(ptr &root) {

  if (root->isLeaf()) {

    this->insertLeaf(root);
    return;
  }

  this->mergeTree(root->left);
  this->mergeTree(root->right);
}

void Node::buildTree(int i) {
  if (this->isLeaf()) {
    if (i == 0) {

      float leftX = (this->box.x() - this->box.rx()) / 2;
      float rightX = (this->box.x() + this->box.rx()) / 2;
      ptr left = std::make_unique<Node>(
          AABB_box(leftX, this->box.y(), this->box.z(), this->box.rx() / 2));
      ptr right = std::make_unique<Node>(
          AABB_box(rightX, this->box.y(), this->box.z(), this->box.rx() / 2));
      left->parent = right->parent = this;
      this->left = std::move(left);
      this->right = std::move(right);

    }

    else if (i == 1) {

      float leftY = (this->box.y() - this->box.ry()) / 2;
      float rightY = (this->box.y() + this->box.ry()) / 2;
      ptr left = std::make_unique<Node>(
          AABB_box(this->box.x(), leftY, this->box.z(), this->box.ry() / 2));
      ptr right = std::make_unique<Node>(
          AABB_box(this->box.x(), rightY, this->box.z(), this->box.ry() / 2));
      left->parent = right->parent = this;
      this->left = std::move(left);
      this->right = std::move(right);

    }

    else {

      float leftZ = (this->box.z() - this->box.rz()) / 2;
      float rightZ = (this->box.z() + this->box.rz()) / 2;
      ptr left = std::make_unique<Node>(
          AABB_box(this->box.x(), this->box.y(), leftZ, this->box.rx() / 2));
      ptr right = std::make_unique<Node>(
          AABB_box(this->box.x(), this->box.y(), rightZ, this->box.rx() / 2));
      left->parent = right->parent = this;
      this->left = std::move(left);
      this->right = std::move(right);
    }

    return;
  }
  this->left->buildTree(i);
  this->right->buildTree(i);
}

bool Node::treeOverlap(ptr &root) { return isOverlap(this->box, root->box); }

bool Node::treeCollision(ptr &root) {

  auto curr = this;
  Node *currRoot = root.get();

  if (!this->treeOverlap(root))
    return false;

  while (!curr->isLeaf()) {

    if (curr->left->treeOverlap(root)) {
      curr = curr->left.get();

    } else {
      curr = curr->right.get();
    }
  }

  while (!currRoot->isLeaf()) {

    if (curr->treeOverlap(currRoot->left))
      currRoot = currRoot->left.get();
    else
      currRoot = currRoot->right.get();
  }

  // resolve collision

  return true;
}

bool Node::boxOverlap(AABB_box &collideBox) {
  return isOverlap(this->box, collideBox);
}
