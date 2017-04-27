#ifndef KDTree_h
#define KDTree_h

#include <algorithm>
#include "Ball.h"

class KDtreeNode {
 public:
  KDtreeNode() = default;

  KDtreeNode* left() { return &this->child[0]; }

  KDtreeNode* right() { return &this->child[1]; }

  unsigned long childSize() { return this->child.size(); }

  unsigned int getPlane() { return this->plane; }

  void build_tree(std::vector<std::shared_ptr<Ball> > v, int depth);
  void treeTraverse();

 private:
  std::vector<KDtreeNode> child;

  std::shared_ptr<Ball> ball;
  unsigned int plane;
};

#endif
