#ifndef KDTree_h
#define KDTree_h

#include "Ball.h"
#include <algorithm>
#include <iostream>

template <class T> class KDtreeNode {

public:
  KDtreeNode() = default;

  KDtreeNode *left() { return &this->child[0]; }

  KDtreeNode *right() { return &this->child[1]; }

  unsigned long childSize() { return this->child.size(); }

  unsigned int getPlane() { return this->plane; }

  void build_tree(std::vector<T> &v, int depth) {
    std::vector<T> v1, v2;
    if (v.empty())
      return;

    if (depth % 3 == 0)
      std::sort(v.begin(), v.end(), sortbyX);
    else if (depth % 3 == 1)
      std::sort(v.begin(), v.end(), sortbyY);
    else
      std::sort(v.begin(), v.end(), sortbyZ);

    this->object = v[v.size() / 2];
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

  void treeTraverse() {
    if (this->childSize() == 0) {
      std::cout << this->object->x() << std::endl;
      std::cout << this->object->y() << std::endl;
      std::cout << this->childSize() << std::endl;
      std::cout << this->getPlane() << std::endl;
      return;
    }

    std::cout << this->object->x() << std::endl;
    std::cout << this->object->y() << std::endl;
    std::cout << this->childSize() << std::endl;
    std::cout << this->getPlane() << std::endl;

    std::cout << "#######left###########" << std::endl;
    this->left()->treeTraverse();

    if (this->childSize() == 2) {
      std::cout << "#######right###########" << std::endl;
      this->right()->treeTraverse();
    }
  }

private:
  std::vector<KDtreeNode> child;

  T object;
  unsigned int plane;
  static bool sortbyX(T lhs, T rhs) { return lhs->x() < rhs->x(); }
  static bool sortbyY(T lhs, T rhs) { return lhs->y() < rhs->y(); }
  static bool sortbyZ(T lhs, T rhs) { return lhs->z() < rhs->z(); }
};

#endif
