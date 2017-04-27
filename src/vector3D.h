#ifndef Vector3D_h
#define Vector3D_h

#include <cmath>
#include <vector>
#include "point.h"

class Vector3D {
 public:
  Vector3D() = default;
  Vector3D(float x, float y, float z);
  Vector3D(Point point);

  Vector3D operator*(float const& scalar);
  Vector3D operator-(Vector3D& rhs);
  Vector3D normal();

  const float& x() const { return vec[0]; }

  const float& y() const { return vec[1]; }

  const float& z() const { return vec[2]; }

  void setX(const float& x) { vec[0] = x; }

  void setY(const float& y) { vec[1] = y; }

  void setZ(const float& z) { vec[2] = z; }

 private:
  std::vector<float> vec;
};

inline float operator*(const Vector3D& lhs, const Vector3D& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

#endif
