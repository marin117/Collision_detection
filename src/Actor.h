#ifndef _Actor_h
#define _Actor_h

#include "AABBTreeNode.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Actor{
public:
    Point center;
    float r;
    ptr root;
    Vector3D vecDir;

    Actor() = default;

    Actor(const Point center,const float r,const float vecX,const float vecY,const float vecZ);
    Actor(const float x,const float y,const float z,const float r,const float vecX,const float vecY,const float vecZ);
    bool isCollision(Actor& collider);
    void drawSphere();
    void updatePosition(const float dt);


};

#endif
