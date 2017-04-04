#ifndef _AABB_box_h
#define _AABB_box_h

#include "point.h"

class AABB_box{
public:


     AABB_box()=default;

     AABB_box(const float x,const float y,const float z,const float r);

     AABB_box(const Point center,const float r);
     AABB_box(const float x,const float y,const float z,const float rx, const float ry, const float rz);
     AABB_box(const Point center,const float rx, const float ry, const float rz);
     AABB_box(const Point center,const float r[]);
     AABB_box& operator=(const AABB_box& src);
     float getSurface();
     float x();
     float y();
     float z();
     float rx();
     float ry();
     float rz();
     Point getCenter();


private:
     Point center;
     float r[3];


};

bool isOverlap(AABB_box a, AABB_box b);
AABB_box Combine(AABB_box a, AABB_box b);

#endif
