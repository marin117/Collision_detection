#include "Actor.h"
#include <iostream>


Actor::Actor(Point center,float r,float velX,float velY,float velZ){


    this->center.x =  center.x;
    this->center.y = center.y;
    this->center.z = center.z;
    this->r = r;
    this->velocity = Vector3D (velX,velY,velZ);
    this->root = std::make_unique<Node>(AABB_box(this->center,this->r));

}

Actor::Actor(float x, float y, float z, float r,float velX,float velY,float velZ){


    this->center.x = x;
    this->center.y = y;
    this->center.z = z;
    this->r = r;
    this->velocity = Vector3D (velX,velY,velZ);
    this->root = std::make_unique<Node>(AABB_box(this->center,this->r));

}

bool Actor::isCollision(Actor& collider){

    return this->root->treeOverlap(collider.root);
}

void Actor::drawSphere(){

    glPushMatrix();
    glTranslatef(this->center.x,this->center.y,this->center.z);
    this->root = std::make_unique<Node>(AABB_box(this->center,this->r));
    glutSolidSphere(this->r,100,10);
    glPopMatrix();


}
void Actor::updatePosition(float dt){
    this->center.x += this->velocity.x() * dt;
    this->center.y += this->velocity.y() * dt;
    this->center.z += this->velocity.z() * dt;
}


