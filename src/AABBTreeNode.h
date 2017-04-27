#ifndef AABBTreeNode_h
#define AABBTreeNode_h

#include <memory>
#include <vector>
#include "AABB_box.h"

class Node {
  typedef std::unique_ptr<Node> ptr;

 public:
  Node() = default;

  Node(const AABB_box bbox);
  Node(ptr& left, ptr& right);

  bool isLeaf();
  void insertLeaf(ptr& leaf);
  void treeTraverse();
  void mergeTree(ptr& root);
  void buildTree(int i);
  bool treeOverlap(ptr& root);
  bool treeCollision(ptr& root);

 private:
  AABB_box box;
  ptr left;
  ptr right;
  Node* parent;
  int height;
};

#endif
