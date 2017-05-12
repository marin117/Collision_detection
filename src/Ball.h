#ifndef Ball_h
#define Ball_h

//#include "AABBTreeNode.h"
#include "Wall.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

class Ball {
public:
  Vector3D vecDir;
  AABB_box bBox;

  Ball() = default;

  Ball(const Point center, const float r, const float vecX, const float vecY,
       const float vecZ, const float m, const uint i);
  Ball(const float x, const float y, const float z, const float r,
       const float vecX, const float vecY, const float vecZ, const float m,
       const uint i);
  void drawSphere();
  void updatePosition(const float dt);
  bool collision(Ball &collider);
  template <typename T> bool collision(T &collider) {
    return isOverlap(this->bBox, collider.bBox);
  }
  void resolveCollision(Ball &collider);
  void resolveCollision(Wall &wall);
  Point &getCenter() { return this->center; }

  const float &x() const { return this->center.x; }

  const float &y() const { return this->center.y; }

  const float &z() const { return this->center.z; }

  const float &rad() const { return this->r; }
  const float &getMass() const { return this->mass; }
  const uint &getI() const { return this->i; }

private:
  Point center;
  float r;
  float mass;
  uint i;
};

#endif
