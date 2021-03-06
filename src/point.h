#ifndef point_h_
#define point_h_

class Point {
 public:
  float x, y, z;

  Point();
  Point(const float x, const float y, const float z);
  friend Point operator-(const Point& lhs, const Point& rhs);
};

Point median(Point a, Point b);

#endif
