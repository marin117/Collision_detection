#ifndef KDTree_h
#define KDTree_h
#include "point.h"
#include "vector3D.h"
#include <algorithm>
#include <iostream>

template <class T> class KDtreeNode {
  static bool sortbyX(T lhs, T rhs) { return lhs.x() < rhs.x(); }
  static bool sortbyY(T lhs, T rhs) { return lhs.y() < rhs.y(); }
  static bool sortbyZ(T lhs, T rhs) { return lhs.z() < rhs.z(); }

public:
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

    this->object = v.at(v.size() / 2);
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
  template <class T1> void searchCollisions(T1 &ball) {

    /*f (ball.collision(this->object)) {
      std::cout << "collision 1" << std::endl;
      ball.resolveCollision(this->object);
      std::cout << ball.vecDir.x() << std::endl;
      std::cout << this->object.vecDir.x() << std::endl;
      // exit(0);
    }

    if (ball.collision(this->left()->object)) {
      std::cout << "collision 2" << std::endl;
      ball.resolveCollision(this->left()->object);
    }*/

    float dist2 = 99999999;

    if (this->childSize() == 0) {
      if (ball.collision(this->object)) {
        std::cout << "KDTreeLeaf " << this->object.vecDir.x() << std::endl;
        std::cout << ball.vecDir.x() << std::endl;
        ball.resolveCollision(this->object);
        std::cout << ball.vecDir.x() << std::endl;
      }

      return;
    }

    if (ball.collision(this->object)) {
      std::cout << "KDTree " << this->object.vecDir.x() << std::endl;
      std::cout << ball.vecDir.x() << std::endl;
      ball.resolveCollision(this->object);
      std::cout << ball.vecDir.x() << std::endl;
    }
    Vector3D vec1(ball.getCenter() - this->left()->object.getCenter());

    float dist1 = vec1 * vec1;

    if (this->childSize() == 2) {

      Vector3D vec2(ball.getCenter() - this->right()->object.getCenter());
      dist2 = vec2 * vec2;
    }

    if (dist1 < dist2 || ball.collision(this->left()->object) ||
        this->childSize() == 1) {
      this->left()->searchCollisions(ball);
    }
    if ((dist1 > dist2 || ball.collision(this->right()->object)) &&
        this->childSize() == 2) {
      this->right()->searchCollisions(ball);
    }
  }

private:
  std::vector<KDtreeNode> child;

  T object;
  unsigned int plane;
};

#endif
