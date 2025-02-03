/*******************************************************************************************************************************
 * @file   collision.cc
 *
 * @brief  Source file for collisions
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <iostream>

/* Inter-component Headers */
#include "math_utils.h"
#include "sphere.h"

/* Intra-component Headers */
#include "collision.h"

bool CollisionDetector::sphereSphere(const RigidBody *a, const RigidBody *b, Contact *contact) {
  auto sphereA = std::dynamic_pointer_cast<Sphere>(a->getShape());
  auto sphereB = std::dynamic_pointer_cast<Sphere>(b->getShape());

  Vector3D aPos = a->getPosition();
  Vector3D bPos = b->getPosition();
  float aRadius = sphereA->getRadius();
  float bRadius = sphereB->getRadius();

  Vector3D normal = bPos - aPos;
  float distanceSquared = normal.lengthSquared();
  float radiusSum = aRadius + bRadius;

  if (distanceSquared > (radiusSum * radiusSum)) {
    return false;
  }

  float distance = normal.length();

  if (contact) {
    /* Normalize the normal vector (if spheres aren't at the same position) */
    if (distance > math::EPSILON) {
      normal = normal * (1.0f / distance);
    } else {
      normal = Vector3D(0, 1, 0); /* Random normal if they are in the same position */
    }

    contact->normal = normal;
    /* Since the distance < radius, this will remain positive */
    contact->penetration = radiusSum - distance;

    /* Contact point is halfway between sphere surfaces */
    contact->point = aPos + (normal * (aRadius + (contact->penetration * 0.5f)));
    contact->bodyA = const_cast<RigidBody *>(a);
    contact->bodyB = const_cast<RigidBody *>(b);

    /* Calculate combined restitution and friction */
    contact->restitution = std::sqrt(sphereA->getRestitution() * sphereB->getRestitution());
    contact->friction = std::sqrt(sphereA->getFriction() * sphereB->getFriction());
  }

  return true;
}

bool CollisionDetector::spherePlane(const RigidBody *sphere, const Vector3D &planeNormal, float planeDistance, Contact *contact) {
  auto sphereShape = std::dynamic_pointer_cast<Sphere>(sphere->getShape());
  if (!sphereShape)
    return false;

  Vector3D pos = sphere->getPosition();
  float radius = sphereShape->getRadius();

  // Calculate distance from sphere center to plane
  float distance = planeNormal.dotProduct(pos) - planeDistance;

  /* Check if sphere is intersecting with plane */
  if (std::abs(distance) > radius) {
    return false;
  }

  // Fill contact information
  if (contact) {
    contact->normal = distance > 0 ? planeNormal * -1.0f : planeNormal;
    contact->penetration = radius - std::abs(distance);
    contact->point = pos - (planeNormal * distance);
    contact->bodyA = const_cast<RigidBody *>(sphere);
    contact->bodyB = nullptr; /* Plane is static */

    /* Set restitution and friction (using sphere values only since plane is static) */
    contact->restitution = sphereShape->getRestitution();
    contact->friction = sphereShape->getFriction();
  }

  return true;
}
