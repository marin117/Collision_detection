#ifndef AABB_box_h
#define AABB_box_h

#include "point.h"

class AABB_box {
public:
  AABB_box() = default;

  AABB_box(const float x, const float y, const float z, const float r);

  AABB_box(const Point center, const float r);
  AABB_box(const float x, const float y, const float z, const float rx,
           const float ry, const float rz);
  AABB_box(const Point center, const float rx, const float ry, const float rz);
  AABB_box(const Point center, const float r[]);
  AABB_box &operator=(const AABB_box &src);
  float getSurface();
  const float &x() const;
  const float &y() const;
  const float &z() const;
  const float &rx() const;
  const float &ry() const;
  const float &rz() const;
  const Point &getCenter() const;

private:
  Point center;
  float r[3];
};

bool isOverlap(AABB_box a, AABB_box b);
AABB_box Combine(AABB_box a, AABB_box b);

#endif
