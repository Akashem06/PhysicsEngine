#pragma once

/*******************************************************************************************************************************
 * @file   matrix_3d.h
 *
 * @brief  Header file for a 3D Matrix library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "vector_3d.h"

/**
 * @defgroup CoreModules
 * @brief    Core modules to run on the CPU for physics management
 * @{
 */

class Matrix3D {
 private:
  static constexpr unsigned int COLS = 3U;
  static constexpr unsigned int ROWS = 3U;

 public:
  float matrix[COLS][ROWS];
  Matrix3D();

  Matrix3D(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

  Matrix3D operator*(const Matrix3D &other) const {
    /* Cache friendly access (Each column is stored sequentiallys)  */
    Matrix3D result;
    for (unsigned int i = 0; i < ROWS; ++i) {
      for (unsigned int j = 0; j < COLS; ++j) {
        result.matrix[i][j] = 0;
        for (unsigned int k = 0; k < COLS; ++k) {
          result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
      }
    }
    return result;
  }

  Vector3D operator*(const Vector3D &vector) const {
    float x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z;
    float y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z;
    float z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z;

    return Vector3D(x, y, z);
  }

  Matrix3D transpose() const;
  float determinant() const;
  Matrix3D inverse() const;
};

/** @} */
