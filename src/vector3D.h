#ifndef Vector3D_h
#define Vector3D_h

#include "point.h"
#include <cmath>
#include <vector>

class Vector3D {
public:
  Vector3D() = default;

  Vector3D(float x, float y, float z) {

    this->vec.emplace_back(x);
    this->vec.emplace_back(y);
    this->vec.emplace_back(z);
  }

  Vector3D(Point point) {

    this->vec.emplace_back(point.x);
    this->vec.emplace_back(point.y);
    this->vec.emplace_back(point.z);
  }

  Vector3D operator*(float const &scalar) {

    return Vector3D(this->x() * scalar, this->y() * scalar, this->z() * scalar);
  }

  Vector3D operator-(Vector3D &rhs) {

    return Vector3D(this->x() - rhs.x(), this->y() - rhs.y(),
                    this->z() - rhs.z());
  }

  Vector3D normal() {
    float mag = std::sqrt(std::pow(this->x(), 2) + std::pow(this->y(), 2) +
                          std::pow(this->z(), 2));
    if (mag == 0) {
      return Vector3D(1, 0, 0);
    }

    return Vector3D(this->x() / mag, this->y() / mag, this->z() / mag);
  }

  const float &x() const { return vec[0]; }

  const float &y() const { return vec[1]; }

  const float &z() const { return vec[2]; }

  void setX(const float &x) { vec[0] = x; }

  void setY(const float &y) { vec[1] = y; }

  void setZ(const float &z) { vec[2] = z; }

private:
  std::vector<float> vec;
};

inline float operator*(const Vector3D &lhs, const Vector3D &rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

#endif
