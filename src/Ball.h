#ifndef Ball_h
#define Ball_h

#include "AABBTreeNode.h"
#include "Wall.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

typedef std::unique_ptr<Node> ptr;

class Ball {
public:
  Vector3D vecDir;
  ptr root;

  Ball() = default;

  Ball(const Point center, const float r, const float vecX, const float vecY,
       const float vecZ);
  Ball(const float x, const float y, const float z, const float r,
       const float vecX, const float vecY, const float vecZ);
  void drawSphere();
  void updatePosition(const float dt);
  bool collision(Ball &collider);
  template <typename T> bool collision(T &collider) {
    return this->root->treeOverlap(collider.root);
  }
  Point getCenter() { return this->center; }

  const float &x() const { return this->center.x; }

  const float &y() const { return this->center.y; }

  const float &z() const { return this->center.z; }

  float rad() { return this->r; }

private:
  Point center;
  float r;
};

#endif
