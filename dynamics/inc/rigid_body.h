#pragma once

/*******************************************************************************************************************************
 * @file   rigid_body.h
 *
 * @brief  Header file for rigid bodies
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <memory>

/* Inter-component Headers */
#include "matrix_3d.h"
#include "shape.h"
#include "vector_3d.h"

/* Intra-component Headers */

/**
 * @defgroup DynamicsModules
 * @brief    Dynamics modules to interactions
 * @{
 */

class RigidBody {
 private:
  std::shared_ptr<Shape> shape;

  // State variables
  Vector3D position;
  Matrix3D orientation;
  Vector3D linearVelocity;
  Vector3D angularVelocity;

  // Force accumulators
  Vector3D force;
  Vector3D torque;

  // Cached physics properties
  float mass;
  float inverseMass;
  Matrix3D inertiaTensor;
  Matrix3D inverseInertiaTensor;

  void updateInertiaTensor();

 public:
  explicit RigidBody(std::shared_ptr<Shape> shape);

  // State
  void setPosition(const Vector3D &pos);
  void setOrientation(const Matrix3D &orient);
  void setLinearVelocity(const Vector3D &vel);
  void setAngularVelocity(const Vector3D &angVel);

  // Force application
  void addForce(const Vector3D &force);
  void addForceAtPoint(const Vector3D &force, const Vector3D &point);
  void addTorque(const Vector3D &torque);
  void clearForces();

  // Getters
  Vector3D getPosition() const;
  Matrix3D getOrientation() const;
  Vector3D getLinearVelocity() const;
  Vector3D getAngularVelocity() const;
  float getMass() const;
  float getInverseMass() const;
  Matrix3D getInertiaTensor() const;
  std::shared_ptr<Shape> getShape() const;

  // Physics simulation
  void integrate(float deltaTime);
};

/** @} */
