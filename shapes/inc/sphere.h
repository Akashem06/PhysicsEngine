#pragma once

/*******************************************************************************************************************************
 * @file   sphere.h
 *
 * @brief  Header file for spheres
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */
#include "matrix_3d.h"
#include "vector_3d.h"

/* Intra-component Headers */
#include "shape.h"

/**
 * @defgroup ShapeModules
 * @brief    Shape modules to define objects
 * @{
 */

class Sphere : public Shape {
 private:
  float radius;
  float density;
  float mass;
  void updateMass();

 public:
  explicit Sphere(float radius, float density = 1.0f);

  float getRadius() const;
  void setRadius(float newRadius);

  // Shape interface implementation
  float getMass() const override;
  float getVolume() const override;
  Matrix3D getInertiaTensor() const override;
  Vector3D getCenterOfMass() const override;
  void updateBoundingBox() override;
  bool isPointInside(const Vector3D &point) const override;
};

/** @} */
