#include "Wall.h"

Wall::Wall (const Point center,const float rX,const float rY,const float rZ,const float vecX,const float vecY,const float vecZ){

    this->center.x =  center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->r[0]= rX;
    this->r[1]= rY;
    this->r[2]= rZ;
    this->vecDir = Vector3D (vecX,vecY,vecZ);
    this->root = std::make_unique<Node>(AABB_box(this->center,this->r));


}

Wall::Wall(const float x,const float y,const float z,const float rX,const float rY,const float rZ,const float vecX,const float vecY,const float vecZ){

    this->center.x = x;
    this->center.y = y;
    this->center.z = z;
    this->r[0]= rX;
    this->r[1]= rY;
    this->r[2]= rZ;
    this->vecDir = Vector3D (vecX,vecY,vecZ);
    this->root = std::make_unique<Node>(AABB_box(this->center,this->r));


}