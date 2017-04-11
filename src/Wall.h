#ifndef _Wall_h
#define _Wall_h


#include "AABBTreeNode.h"
#include "vector3D.h"
#include <GL/gl.h>
#include <GL/glut.h>

class Wall{
public:
    Point center;
    float r[3];
    ptr root;
    Vector3D vecDir;

    Wall() = default;
    Wall (const Point center,const float rX,const float rY,const float rZ,const float vecX,const float vecY,const float vecZ);
    Wall(const float x,const float y,const float z,const float rX,const float rY,const float rZ,const float vecX,const float vecY,const float vecZ);


};

#endif
