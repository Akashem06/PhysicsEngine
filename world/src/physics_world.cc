/*******************************************************************************************************************************
 * @file   physics_world.cc
 *
 * @brief  Source file for the world physics
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <algorithm>
#include <iostream>

/* Inter-component Headers */

/* Intra-component Headers */
#include "physics_world.h"

PhysicsWorld::PhysicsWorld() {
  this->gravity = Vector3D(0, -9.81f, 0);
  this->timeStep = 1.0f / 60.0f;
}

void PhysicsWorld::setGravity(const Vector3D &gravity) {
  this->gravity = gravity;
}

void PhysicsWorld::setTimeStep(float step) {
  this->timeStep = step;
}

void PhysicsWorld::addRigidBody(std::shared_ptr<RigidBody> body) {
  bodies.push_back(body);
}

void PhysicsWorld::removeRigidBody(std::shared_ptr<RigidBody> body) {
  bodies.erase(std::remove(bodies.begin(), bodies.end(), body), bodies.end());
}

size_t PhysicsWorld::getBodyCount() const {
  return bodies.size();
}

std::vector<std::shared_ptr<RigidBody>> PhysicsWorld::getBodies() const {
  return bodies;
}

void PhysicsWorld::detectCollisions() {
  contacts.clear();

  /* Check all pairs of bodies. O(N^2) */
  for (size_t i = 0; i < bodies.size(); i++) {
    for (size_t j = i + 1; j < bodies.size(); j++) {
      Contact contact;
      if (CollisionDetector::sphereSphere(bodies[i].get(), bodies[j].get(), &contact)) {
        contacts.push_back(contact);
      }
    }
  }
}

void PhysicsWorld::resolveCollisions() {
  for (const auto &contact : contacts) {
    if (!contact.bodyA || !contact.bodyB)
      continue;

    /* Calculate relative velocity */
    Vector3D relativeVel = contact.bodyB->getLinearVelocity() - contact.bodyA->getLinearVelocity();

    /* Calculate impulse */
    float velAlongNormal = relativeVel.dotProduct(contact.normal);
    if (velAlongNormal > 0)
      continue; /* Bodies are seperating already */

    float j = -(1.0f + contact.restitution) * velAlongNormal;
    j /= contact.bodyA->getInverseMass() + contact.bodyB->getInverseMass();

    Vector3D impulse = contact.normal * j;

    // Apply impulse
    contact.bodyA->setLinearVelocity(contact.bodyA->getLinearVelocity() - impulse * contact.bodyA->getInverseMass());
    contact.bodyB->setLinearVelocity(contact.bodyB->getLinearVelocity() + impulse * contact.bodyB->getInverseMass());
  }
}

void PhysicsWorld::integrateForces() {
  for (auto &body : bodies) {
    body->addForce(gravity * body->getMass());
    body->integrate(timeStep);
  }
}

void PhysicsWorld::step() {
  detectCollisions();
  resolveCollisions();
  integrateForces();
}

void PhysicsWorld::reset() {
  bodies.clear();
  contacts.clear();
}
