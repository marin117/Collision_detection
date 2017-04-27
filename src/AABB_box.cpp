#include "AABB_box.h"
#include <stdio.h>
#include <algorithm>
#include <cmath>

AABB_box::AABB_box(const float x, const float y, const float z, const float r) {
  center.x = x;
  center.y = y;
  center.z = z;
  this->r[0] = r;
  this->r[1] = r;
  this->r[2] = r;
}

AABB_box::AABB_box(const Point center, const float r) {
  this->center = center;
  this->r[0] = r;
  this->r[1] = r;
  this->r[2] = r;
}

AABB_box::AABB_box(const Point center, const float rx, const float ry,
                   const float rz) {
  this->center = center;
  this->r[0] = rx;
  this->r[1] = ry;
  this->r[2] = rz;
}
AABB_box::AABB_box(const float x, const float y, const float z, const float rx,
                   const float ry, const float rz) {
  center.x = x;
  center.y = y;
  center.z = z;
  this->r[0] = rx;
  this->r[1] = ry;
  this->r[2] = rz;
}

AABB_box::AABB_box(const Point center, const float r[]) {
  this->center = center;
  this->r[0] = r[0];
  this->r[1] = r[1];
  this->r[2] = r[2];
}

const Point &AABB_box::getCenter() const { return this->center; }

const float &AABB_box::rx() const { return this->r[0]; }

const float &AABB_box::ry() const { return this->r[1]; }

const float &AABB_box::rz() const { return this->r[2]; }

float AABB_box::getSurface() { return r[0] * r[1] * r[2]; }

AABB_box &AABB_box::operator=(const AABB_box &src) {
  this->center = src.center;
  this->r[0] = src.r[0];
  this->r[1] = src.r[1];
  this->r[2] = src.r[2];

  return *this;
}

bool isOverlap(AABB_box a, AABB_box b) {
  if (((std::abs(a.x() - b.x()) > (a.rx() + b.rx())) ||
       (std::abs(a.y() - b.y()) > (a.ry() + b.ry())) ||
       (std::abs(a.z() - b.z()) > (a.rz() + b.rz()))))
    return false;

  return true;
}

AABB_box Combine(AABB_box a, AABB_box b) {
  float dist = (std::sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2) +
                          pow(a.z() - b.z(), 2)) /
                2) +
               std::abs(std::max(a.rx(), b.rx()));

  AABB_box combined(median(a.getCenter(), b.getCenter()), dist);

  return combined;
}
