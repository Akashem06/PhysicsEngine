/*******************************************************************************************************************************
 * @file   sphere.cc
 *
 * @brief  Source file for the sphere object
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <iostream>

/* Inter-component Headers */
#include "math_utils.h"

/* Intra-component Headers */
#include "sphere.h"

void Sphere::updateMass() {
  this->mass = this->density * getVolume();
}

Sphere::Sphere(float radius, float density) {
  this->radius = radius;
  this->density = density;

  updateMass();
}

float Sphere::getRadius() const {
  return this->radius;
}

void Sphere::setRadius(float newRadius) {
  if (newRadius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }
  this->radius = newRadius;
}

float Sphere::getMass() const {
  return this->mass;
}

float Sphere::getVolume() const {
  return (4.0f / 3.0f) * math::PI * this->radius * this->radius * this->radius;
}

Matrix3D Sphere::getInertiaTensor() const {
  /* For a solid sphere the inertia is equal to: */
  /* I = (2/5) * Mass * Radius^2 */
  float i = (2.0f / 5.0f) * mass * radius * radius;

  /* Diagnoal matrix with the moment of inertia */
  return Matrix3D(i, 0, 0, 0, i, 0, 0, 0, i);
}

Vector3D Sphere::getCenterOfMass() const {
  /* Center of mass of a sphere is at the center */
  return this->position;
}

void Sphere::updateBoundingBox() {
  Vector3D extent(this->radius, this->radius, this->radius);
  this->boundingBoxMin = this->position - extent;
  this->boundingBoxMax = this->position + extent;
}

bool Sphere::isPointInside(const Vector3D &point) const {
  /* Distance from the distance to the point. Norm of Distance vec - position */
  Vector3D distanceVec = point - position;
  float distanceSquared = distanceVec.dotProduct(distanceVec);

  return distanceSquared <= (radius * radius);
}
