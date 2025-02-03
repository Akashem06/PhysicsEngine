#pragma once

/*******************************************************************************************************************************
 * @file   collision.h
 *
 * @brief  Header file for collisions
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <memory>

/* Inter-component Headers */
#include "matrix_3d.h"
#include "rigid_body.h"
#include "shape.h"
#include "vector_3d.h"

/* Intra-component Headers */

/**
 * @defgroup CollisionModules
 * @brief    Collision modules for handling interactions
 * @{
 */

struct Contact {
  Vector3D point;    /**< World space contact point */
  Vector3D normal;   /**< Contact normal vector */
  float penetration; /**< Penetration depth */
  RigidBody *bodyA;  /**< Collision object A */
  RigidBody *bodyB;  /**< Collision object B */
  float restitution; /**< Combined restitution */
  float friction;    /**< Combined friction */
};

class CollisionDetector {
 public:
  static bool sphereSphere(const RigidBody *a, const RigidBody *b, Contact *contact);
  static bool spherePlane(const RigidBody *sphere, const Vector3D &planeNormal, float planeDistance, Contact *contact);
};

/** @} */
