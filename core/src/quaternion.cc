/*******************************************************************************************************************************
 * @file   quaternion.cc
 *
 * @brief  Source file for a Quaternion library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "quaternion.h"

Quaternion::Quaternion() {
  this->w = 1.0f;
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
  this->w = w;
  this->x = x;
  this->y = y;
  this->z = z;
}

static Quaternion Quaternion::fromAxisAngle(const Vector3D &axis, float angle) {}

Quaternion Quaternion::normalize() const {}

Quaternion Quaternion::conjugate() const {}

Matrix3D Quaternion::toRotationMatrix() const {}

static Quaternion Quaternion::slerp(const Quaternion &q1, const Quaternion &q2, float t) {}
