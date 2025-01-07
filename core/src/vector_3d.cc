/*******************************************************************************************************************************
 * @file   vector_3d.cc
 *
 * @brief  Source file for a 3D Vector library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <cmath>

/* Inter-component Headers */

/* Intra-component Headers */
#include "vector_3d.h"

Vector3D::Vector3D() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float Vector3D::length() const {
  return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

float Vector3D::lengthSquared() const {
  return ((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector3D Vector3D::normalize() const {
  float vectorLength = length();
  return vectorLength > 0.0f ? (*this / vectorLength) : *this;
}

float Vector3D::dotProduct(const Vector3D &vector) const {
  return ((this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z));
}

Vector3D Vector3D::crossProduct(const Vector3D &vector) const {
  return Vector3D(((this->y * vector.z) - (this->z * vector.y)), ((this->z * vector.x) - (this->x * vector.z)), ((this->x * vector.y) - (this->y * vector.x)));
}
