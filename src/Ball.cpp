#include "Ball.h"
#include <iostream>

Ball::Ball(const Point center, const float r, const float vecX,
           const float vecY, const float vecZ) {
  this->center.x = center.x;
  this->center.y = center.y;
  this->center.z = center.z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->root = std::make_unique<Node>(AABB_box(this->center, this->r));
}

Ball::Ball(const float x, const float y, const float z, const float r,
           const float vecX, const float vecY, const float vecZ) {
  this->center.x = x;
  this->center.y = y;
  this->center.z = z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->root = std::make_unique<Node>(AABB_box(this->center, this->r));
}

bool Ball::isBallCollision(Ball& collider) {
  Vector3D dist(this->center - collider.center);

  float squared_dist = dist * dist;

  float squared_rad = (this->r + collider.r) * (this->r + collider.r);

  return squared_dist <= squared_rad;
}

void Ball::drawSphere() {
  glPushMatrix();
  glTranslatef(this->center.x, this->center.y, this->center.z);
  this->root = std::make_unique<Node>(AABB_box(this->center, this->r));
  glutSolidSphere(this->r, 100, 10);
  glPopMatrix();
}
void Ball::updatePosition(float dt) {
  this->center.x += this->vecDir.x() * dt;
  this->center.y += this->vecDir.y() * dt;
  this->center.z += this->vecDir.z() * dt;
}

bool Ball::isWallCollision(Wall& wall) {
  return this->root->treeOverlap(wall.root);
}
