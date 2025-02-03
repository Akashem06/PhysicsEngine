/*******************************************************************************************************************************
 * @file   rigid_body.cc
 *
 * @brief  Source file for rigid bodies
 *
 * @date   2025-01-28
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <iostream>

/* Inter-component Headers */
#include "math_utils.h"

/* Intra-component Headers */
#include "rigid_body.h"

void RigidBody::updateInertiaTensor() {
  this->inertiaTensor = shape->getInertiaTensor();
  this->inverseInertiaTensor = inertiaTensor.inverse();

  /* Checking if the mass is non-negative and not zero */
  this->inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f;
}

RigidBody::RigidBody(std::shared_ptr<Shape> shape) {
  this->shape = shape;
  this->shape->getPosition();
  this->orientation = Matrix3D();

  this->linearVelocity = Vector3D(0, 0, 0);
  this->angularVelocity = Vector3D(0, 0, 0);
  this->force = Vector3D(0, 0, 0);
  this->torque = Vector3D(0, 0, 0);

  this->position = getPosition();
  this->mass = getMass();
  updateInertiaTensor();
}

void RigidBody::setPosition(const Vector3D &pos) {
  this->position = pos;
  this->shape->setPosition(pos);
}

void RigidBody::setOrientation(const Matrix3D &orient) {
  this->orientation = orient;
  this->shape->setOrientation(orient);
}

void RigidBody::setLinearVelocity(const Vector3D &vel) {
  this->linearVelocity = vel;
}

void RigidBody::setAngularVelocity(const Vector3D &angVel) {
  this->angularVelocity = angVel;
}

void RigidBody::addForce(const Vector3D &force) {
  this->force = this->force + force;
}

void RigidBody::addForceAtPoint(const Vector3D &force, const Vector3D &point) {
  this->force = this->force + force;

  /* Torque = Force X Radius */
  Vector3D radius = point - this->position;
  this->torque = this->torque + (radius.crossProduct(force));
}

void RigidBody::addTorque(const Vector3D &torque) {
  this->torque = this->torque + torque;
}

void RigidBody::clearForces() {
  this->force = Vector3D(0, 0, 0);
  this->torque = Vector3D(0, 0, 0);
}

Vector3D RigidBody::getPosition() const {
  return this->shape->getPosition();
}

Matrix3D RigidBody::getOrientation() const {
  return this->orientation;
}

Vector3D RigidBody::getLinearVelocity() const {
  return this->linearVelocity;
}

Vector3D RigidBody::getAngularVelocity() const {
  return this->angularVelocity;
}

float RigidBody::getMass() const {
  return this->shape->getMass();
}

float RigidBody::getInverseMass() const {
  if (this->shape->getMass() == 0.0f) {
    /* Assume mass of 1 */
    return 1.0f;
  }

  return (1.0f / this->shape->getMass());
}

Matrix3D RigidBody::getInertiaTensor() const {
  return this->shape->getInertiaTensor();
}

std::shared_ptr<Shape> RigidBody::getShape() const {
  return this->shape;
}

void RigidBody::integrate(float deltaTime) {
  /* Objects with no mass don't move */
  if (inverseMass <= 0.0f) {
    return;
  }

  /* Velocity = Vinitial + Accel * dT */
  this->linearVelocity = this->linearVelocity + ((force * inverseMass) * deltaTime);

  /* Position = PosInitial + Vel * dT */
  this->position = this->position + (this->linearVelocity * deltaTime);

  /* Torque = AngularAccel * InertiaTensor */
  /* AngularAccel = InverseInertiaTensor * Torque */
  Vector3D angularAcceleration = inverseInertiaTensor * torque;

  /* Integrate the acceleration for velocity */
  this->angularVelocity = this->angularVelocity + angularAcceleration * deltaTime;

  /* Skew symmetric matrix instead of using cross products */
  Matrix3D spin(0, -angularVelocity.z, angularVelocity.y, angularVelocity.z, 0, -angularVelocity.x, -angularVelocity.y, angularVelocity.x, 0);

  /* Update orientation quaternion (R' = R + (w x R)dt) */
  this->orientation = this->orientation + ((spin * this->orientation) * deltaTime);

  /* Normalize the orientation matrix to prevent drift */
  if (!this->orientation.isOrthonormal()) {
    this->orientation.orthonormalize();
  }

  /* Update shapes position and orientation */
  shape->setPosition(position);
  shape->setOrientation(orientation);

  clearForces();
}
