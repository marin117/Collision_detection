#ifndef Wall_h
#define Wall_h

#include "AABBTreeNode.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Wall {
  typedef std::unique_ptr<Node> ptr;

public:
  ptr root;
  Vector3D vecDir;

  Wall() = default;
  Wall(const Point center, const float rX, const float rY, const float rZ,
       const float vecX, const float vecY, const float vecZ);
  Wall(const float x, const float y, const float z, const float rX,
       const float rY, const float rZ, const float vecX, const float vecY,
       const float vecZ);
  const float &x() const { return this->center.x; }

  const float &y() const { return this->center.y; }

  const float &z() const { return this->center.z; }

private:
  Point center;
  float r[3];
};

#endif
