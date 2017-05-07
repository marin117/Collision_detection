#include "Ball.h"

Ball::Ball(const Point center, const float r, const float vecX,
           const float vecY, const float vecZ, const float m) {
  this->center.x = center.x;
  this->center.y = center.y;
  this->center.z = center.z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->bBox = AABB_box(this->center, this->r);
  this->mass = m;
}

Ball::Ball(const float x, const float y, const float z, const float r,
           const float vecX, const float vecY, const float vecZ,
           const float m) {
  this->center.x = x;
  this->center.y = y;
  this->center.z = z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->bBox = AABB_box(this->center, this->r);
  this->mass = m;
}

bool Ball::collision(Ball &collider) {

  Vector3D dist(this->center - collider.center);

  float squared_dist = dist * dist;

  float squared_rad = (this->r + collider.r) * (this->r + collider.r);

  return squared_dist <= squared_rad;
}

void Ball::drawSphere() {
  glPushMatrix();
  glTranslatef(this->center.x, this->center.y, this->center.z);
  this->bBox = AABB_box(this->center, this->r);
  glutSolidSphere(this->r, 100, 10);
  glPopMatrix();
}
void Ball::updatePosition(float dt) {
  float acc = -9.81;
  float v = this->vecDir.y();
  this->vecDir.setY(v + acc * dt);
  std::cout << "brzina" << v + acc * dt << std::endl;
  this->center.x += this->vecDir.x() * dt;
  this->center.y += this->vecDir.y() * dt;
  this->center.z += this->vecDir.z() * dt;
}

void Ball::resolveCollision(Ball &collider) {
  Vector3D v_n(this->getCenter() - collider.getCenter());
  Vector3D v_un = v_n.normal();
  Vector3D v_ut(-v_un.y(), v_un.x(), v_un.z());

  float v1n = v_un * this->vecDir;
  float v1t = v_ut * this->vecDir;

  float v2n = v_un * collider.vecDir;
  float v2t = v_ut * collider.vecDir;
  std::cout << "resolve0: " << this->vecDir.x() << std::endl;
  std::cout << "resolve02: " << collider.vecDir.x() << std::endl;

  float v1x =
      (v1n * (this->mass - collider.getMass()) + 2 * collider.getMass() * v2n) /
      (this->mass + collider.getMass()) * v_un.x();
  float v1y =
      (v1n * (this->mass - collider.getMass()) + 2 * collider.getMass() * v2n) /
      (this->mass + collider.getMass()) * v_un.y();

  float v2x = (v2n * (collider.getMass() - this->mass) + 2 * this->mass * v1n) /
              (this->mass + collider.getMass()) * v_un.x();

  float v2y = (v2n * (collider.getMass() - this->mass) + 2 * this->mass * v1n) /
              (this->mass + collider.getMass()) * v_un.y();

  this->vecDir.setX(v1x + v1t * v_ut.x());
  this->vecDir.setY(v1y + v1t * v_ut.y());

  collider.vecDir.setX(v2x + v2t * v_ut.x());
  collider.vecDir.setY(v2y + v2t * v_ut.y());
}

void Ball::resolveCollision(Wall &collider) {
  /*float dot = this->vecDir * wall.vecDir;
  float doubleDot = dot * 2;
  Vector3D newNorm = wall.vecDir * doubleDot;
  this->vecDir = this->vecDir - newNorm;*/

  float v1x = std::abs((this->vecDir.x() * (this->mass - collider.getMass())) /
                       (this->mass + collider.getMass()));
  float v1y = std::abs((this->vecDir.y() * (this->mass - collider.getMass())) /
                       (this->mass + collider.getMass()));

  this->vecDir.setX(v1x);
  this->vecDir.setY(v1y);
}
