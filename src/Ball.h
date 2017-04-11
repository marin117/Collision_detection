#ifndef _Ball_h
#define _Ball_h

#include "AABBTreeNode.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Ball{
public:
    Point center;
    float r;
    ptr root;
    Vector3D vecDir;

    Ball() = default;

    Ball(const Point center,const float r,const float vecX,const float vecY,const float vecZ);
    Ball(const float x,const float y,const float z,const float r,const float vecX,const float vecY,const float vecZ);
    bool isCollision(Ball& collider);
    void drawSphere();
    void updatePosition(const float dt);


};

#endif
