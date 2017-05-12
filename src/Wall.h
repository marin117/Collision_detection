#ifndef Wall_h
#define Wall_h

#include "AABB_box.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Wall {

public:
  AABB_box bBox;
  Vector3D vecDir;

  Wall() = default;
  Wall(const Point center, const float rX, const float rY, const float rZ,
       const float vecX, const float vecY, const float vecZ, const float m);
  Wall(const float x, const float y, const float z, const float rX,
       const float rY, const float rZ, const float vecX, const float vecY,
       const float vecZ, const float m);
  const float &x() const { return this->center.x; }

  const float &y() const { return this->center.y; }

  const float &z() const { return this->center.z; }
  const float &getMass() const { return this->mass; }
  Point &getCenter() { return this->center; }

private:
  Point center;
  float r[3];
  float mass;
  uint i;
};

#endif
