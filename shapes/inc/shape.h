#pragma once

/*******************************************************************************************************************************
 * @file   shape.h
 *
 * @brief  Header file for shapes
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */
#include "matrix_3d.h"
#include "vector_3d.h"

/* Intra-component Headers */

/**
 * @defgroup ShapeModules
 * @brief    Shape modules to define objects
 * @{
 */

class Shape {
 protected:
  Vector3D position;
  Matrix3D orientation;
  Vector3D boundingBoxMin;
  Vector3D boundingBoxMax;

 public:
  virtual ~Shape() = default;

  /** @brief    Measurement of bounciness */
  float restitution{0.5f};
  /** @brief    Measurement of friction */
  float friction{0.3f};

  // Transform getters/setters
  virtual void setPosition(const Vector3D &pos) {
    this->position = pos;
  }

  virtual void setOrientation(const Matrix3D &orient) {
    this->orientation = orient;
  }

  virtual Vector3D getPosition() const {
    return this->position;
  }

  virtual Matrix3D getOrientation() const {
    return this->orientation;
  }

  // Physics properties
  virtual float getMass() const = 0;
  virtual float getVolume() const = 0;
  virtual Matrix3D getInertiaTensor() const = 0;
  virtual Vector3D getCenterOfMass() const = 0;

  // Collision detection
  virtual void updateBoundingBox() = 0;
  virtual bool isPointInside(const Vector3D &point) const = 0;

  // Bounding box access
  Vector3D getBoundingBoxMin() const {
    return boundingBoxMin;
  }

  Vector3D getBoundingBoxMax() const {
    return boundingBoxMax;
  }

  /* Restitution and friction getters */
  float getRestitution() const {
    return restitution;
  }

  float getFriction() const {
    return friction;
  }
};

/** @} */
