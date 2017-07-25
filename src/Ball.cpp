#include "Ball.h"

Ball::Ball(const Point center, const float r, const float vecX,
           const float vecY, const float vecZ, const float m, const uint i) {
  this->center.x = center.x;
  this->center.y = center.y;
  this->center.z = center.z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->bBox = AABB_box(this->center, this->r);
  this->mass = m;
  this->i = i;
}

Ball::Ball(const float x, const float y, const float z, const float r,
           const float vecX, const float vecY, const float vecZ, const float m,
           const uint i) {
  this->center.x = x;
  this->center.y = y;
  this->center.z = z;
  this->r = r;
  this->vecDir = Vector3D(vecX, vecY, vecZ);
  this->bBox = AABB_box(this->center, this->r);
  this->mass = m;
  this->i = i;
}

bool Ball::collision(Ball &collider) {
  if (this->i == collider.getI())
    return false;

  Vector3D dist(this->center - collider.center);

  float squared_dist = dist * dist;

  float squared_rad = (this->r + collider.r) * (this->r + collider.r);

  return squared_dist <= squared_rad;
}

void Ball::drawSphere(unsigned int program, int matrix, glm::mat4 &view,
                      glm::mat4 &projection) {
  /*  glPushMatrix();
    glTranslatef(this->center.x, this->center.y, this->center.z);
    this->bBox = AABB_box(this->center, this->r);
    glutSolidSphere(this->r, 100, 10);
    glPopMatrix();*/

  glm::mat4 Model = glm::mat4(1.0f);
  glm::vec3 position = glm::vec3(this->x(), this->y(), this->z());
  glm::vec3 radius = glm::vec3(1.0f, 1.0f, 1.0f) * this->r;
  Model = glm::scale(Model, radius);
  Model = glm::translate(Model, position);
  glm::mat4 mvp = projection * view * Model;
  glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
  glUseProgram(program);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Ball::updatePosition(float dt) {
  double acc = -9.81;
  this->vecDir.setY(this->vecDir.y() + acc * dt);
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

  float v1x =
      (v1n * (this->mass - collider.getMass()) + 2 * collider.getMass() * v2n) /
      (this->mass + collider.getMass()) * v_un.x();
  float v1y =
      (v1n * (this->mass - collider.getMass()) + 2 * collider.getMass() * v2n) /
      (this->mass + collider.getMass()) * v_un.y();

  this->vecDir.setX(v1x + v1t * v_ut.x());
  this->vecDir.setY(v1y + v1t * v_ut.y());
}

void Ball::resolveCollision(Wall &collider) {

  float dot = this->vecDir * collider.vecDir;
  float doubleDot = dot * 2;
  Vector3D newNorm = collider.vecDir * doubleDot;
  this->vecDir = this->vecDir - newNorm;
  /*if (collider.vecDir.x() != 0) {
    float v1x =
        std::abs((this->vecDir.x() * (this->mass - collider.getMass())) /
                 (this->mass + collider.getMass()));
    this->vecDir.setX(v1x);
  }*/

  if (collider.vecDir.y() != 0.0) {
    float v1y =
        std::abs((this->vecDir.y() * (this->mass - collider.getMass())) /
                 (this->mass + collider.getMass()));

    this->vecDir.setY(v1y);
  }
}
