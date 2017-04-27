#include "KDTree.h"
#include <iostream>
#include <memory>

inline bool sortbyX(std::shared_ptr<Ball> lhs, std::shared_ptr<Ball> rhs) {
  return lhs->x() < rhs->x();
}
inline bool sortbyY(std::shared_ptr<Ball> lhs, std::shared_ptr<Ball> rhs) {
  return lhs->y() < rhs->y();
}
inline bool sortbyZ(std::shared_ptr<Ball> lhs, std::shared_ptr<Ball> rhs) {
  return lhs->z() < rhs->z();
}

void KDtreeNode::build_tree(std::vector<std::shared_ptr<Ball> > v, int depth) {
  std::vector<std::shared_ptr<Ball> > v1, v2;
  if (v.empty()) return;

  if (depth % 3 == 0)
    std::sort(v.begin(), v.end(), sortbyX);
  else if (depth % 3 == 1)
    std::sort(v.begin(), v.end(), sortbyY);
  else
    std::sort(v.begin(), v.end(), sortbyZ);

  this->ball = v[v.size() / 2];
  this->plane = depth % 3;

  for (unsigned int i = 0; i < v.size(); ++i) {
    if (i < v.size() / 2) {
      v1.emplace_back(v[i]);
    } else if (i > v.size() / 2) {
      v2.emplace_back(v[i]);
    } else
      continue;
  }
  if (v1.size() >= 1 && v2.size() >= 1) {
    this->child.emplace_back(KDtreeNode());
    this->child.emplace_back(KDtreeNode());

    this->left()->build_tree(v1, ++depth);
    this->right()->build_tree(v2, ++depth);
  }

  else if (v1.size() == 1 && v2.empty()) {
    this->child.emplace_back(KDtreeNode());
    this->left()->build_tree(v1, ++depth);

  }

  else if (v1.empty() && v2.size() == 1) {
    this->child.emplace_back(KDtreeNode());
    this->left()->build_tree(v2, ++depth);
  } else
    return;
}

void KDtreeNode::treeTraverse() {
  if (this->childSize() == 0) {
    std::cout << this->ball->x() << std::endl;
    std::cout << this->ball->y() << std::endl;
    std::cout << this->childSize() << std::endl;
    std::cout << this->getPlane() << std::endl;
    return;
  }

  std::cout << this->ball->x() << std::endl;
  std::cout << this->ball->y() << std::endl;
  std::cout << this->childSize() << std::endl;
  std::cout << this->getPlane() << std::endl;

  std::cout << "#######left###########" << std::endl;
  this->left()->treeTraverse();

  if (this->childSize() == 2) {
    std::cout << "#######right###########" << std::endl;
    this->right()->treeTraverse();
  }
}
