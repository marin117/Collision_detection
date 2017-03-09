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
    float k;
    ptr root;
    Vector3D velocity;

    Actor() = default;

    Actor(Point center,float r,float velX,float velY,float velZ);
    Actor(float x, float y, float z,float r,float velX,float velY,float velZ);
    bool isCollision(Actor& collider);
    void resolveCollision(float k);
    void drawSphere();
    void updatePosition(float dt);


};

#endif
