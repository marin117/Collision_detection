#include "Actor.h"


Actor::Actor(Point center,float r){


    this->center.x =  center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    glPushMatrix();
    this->root = std::make_unique<Node>(AABB_box(this->center,r));
    glTranslatef(this->center.x,this->center.y,this->center.z);
    glutSolidSphere(r,100,10);
    glPopMatrix();

}

Actor::Actor(float x, float y, float z, float r){


    this->center.x = x;
    this->center.y = y;
    this->center.z = z;
    glPushMatrix();
    glTranslatef(this->center.x,this->center.y,this->center.z);
    this->root = std::make_unique<Node>(AABB_box(this->center,r));
    glutSolidSphere(r,100,10);
    glPopMatrix();

}

bool Actor::isCollision(Actor& collider){

    return this->root->treeOverlap(collider.root);
}

