#pragma once

/*******************************************************************************************************************************
 * @file   physics_world.h
 *
 * @brief  Header file for world physics
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <vector>

/* Inter-component Headers */
#include "collision.h"
#include "matrix_3d.h"
#include "rigid_body.h"
#include "shape.h"
#include "vector_3d.h"

/* Intra-component Headers */

/**
 * @defgroup WorldModules
 * @brief    World modules for environment definitions
 * @{
 */

class PhysicsWorld {
 public:
  PhysicsWorld();

  // World configuration
  void setGravity(const Vector3D &gravity);
  void setTimeStep(float step);

  // Object management
  void addRigidBody(std::shared_ptr<RigidBody> body);
  void removeRigidBody(std::shared_ptr<RigidBody> body);

  // Simulation
  void step();
  void reset();

  // Access
  size_t getBodyCount() const;
  std::vector<std::shared_ptr<RigidBody>> getBodies() const;

 private:
  std::vector<std::shared_ptr<RigidBody>> bodies;
  std::vector<Contact> contacts;

  Vector3D gravity;
  float timeStep;

  void detectCollisions();
  void resolveCollisions();
  void integrateForces();
};

/** @} */
