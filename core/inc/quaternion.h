#pragma once

/*******************************************************************************************************************************
 * @file   quaternion.h
 *
 * @brief  Header file for a Quaternion library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "matrix_3d.h"
#include "vector_3d.h"

/**
 * @defgroup CoreModules
 * @brief    Core modules to run on the CPU for physics management
 * @{
 */

class Quaternion {
 public:
  float w, x, y, z;

  Quaternion();
  Quaternion(float w, float x, float y, float z);

  static Quaternion fromAxisAngle(const Vector3D &axis, float angle);

  Quaternion operator*(const Quaternion &q) const;
  Vector3D operator*(const Vector3D &v) const;
  Quaternion normalize() const;
  Quaternion conjugate() const;
  Matrix3D toRotationMatrix() const;

  static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t);
};

/** @} */
