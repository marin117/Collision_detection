#ifndef _Actor_h
#define _Actor_h

#include "AABBTreeNode.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Actor{
public:
    Point center;
    float r;
    float speed;
    float k;
    ptr root;

    Actor() = default;

    Actor(Point center,float r,float speed,float k);
    Actor(float x, float y, float z,float r,float speed,float k);
    bool isCollision(Actor collider);
    void resolveCollision(Actor collider);


};

#endif
