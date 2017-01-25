#ifndef _AABB_box_h
#define _AABB_box_h

#include "point.h"

class AABB_box{
public:
     Point center;
     float r[3];

     AABB_box()=default;

     AABB_box(const float x,const float y,const float z,const float r);

     AABB_box(const Point center,const float r);
     
     AABB_box& operator=(const AABB_box& src);

};

bool isOverlap(AABB_box a, AABB_box b);
AABB_box Combine(AABB_box a, AABB_box b);

#endif
