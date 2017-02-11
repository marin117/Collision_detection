#include "Actor.h"


Actor::Actor(Point center,float r,float speed,float k){

    this->speed = speed;
    this->k = k;
    this->center.x = this->speed + center.x;
    this->center.y = this->k * this->center.x + center.y;
    this->center.z = center.z;
    this->root = std::make_unique<Node>(AABB_box(this->center,r));
    glPushMatrix();
    glTranslatef(this->center.x,this->center.y,this->center.z);
    glutSolidSphere(r,100,10);
    glPopMatrix();

}

Actor::Actor(float x, float y, float z, float r, float speed, float k){

    this->speed = speed;
    this->k = k;
    this->center.x = this->speed + center.x;
    this->center.y = this->k * this->center.x + y;
    this->center.z = z;
    this->root = std::make_unique<Node>(AABB_box(this->center,r));
    glPushMatrix();
    glTranslatef(this->center.x,this->center.y,this->center.z);
    glutSolidSphere(r,100,10);
    glPopMatrix();

}
