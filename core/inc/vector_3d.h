#pragma once

/*******************************************************************************************************************************
 * @file   vector_3d.h
 *
 * @brief  Header file for a 3D Vector library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */

/**
 * @defgroup CoreModules
 * @brief    Core modules to run on the CPU for physics management
 * @{
 */

class Vector3D {
 public:
  float x, y, z;

  Vector3D();
  Vector3D(float x, float y, float z);

  Vector3D operator+(const Vector3D &vector) const {
    return Vector3D(this->x + vector.x, this->y + vector.y, this->z + vector.z);
  };

  Vector3D operator-(const Vector3D &vector) const {
    return Vector3D(this->x - vector.x, this->y - vector.y, this->z - vector.z);
  };

  Vector3D operator*(float scale) const {
    return Vector3D(this->x * scale, this->y * scale, this->z * scale);
  };

  Vector3D operator/(float scale) const {
    return Vector3D(this->x / scale, this->y / scale, this->z / scale);
  };

  float length() const;
  float lengthSquared() const;
  Vector3D normalize() const;
  float dotProduct(const Vector3D &vector) const;
  Vector3D crossProduct(const Vector3D &vector) const;
};

/** @} */
