/*******************************************************************************************************************************
 * @file   matrix_3d.cc
 *
 * @brief  Source file for a 3D Matrix library
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <iostream>

/* Inter-component Headers */

/* Intra-component Headers */
#include "matrix_3d.h"

Matrix3D::Matrix3D() {
  /* Identity matrix */
  for (unsigned int row = 0U; row < ROWS; row++) {
    for (unsigned int col = 0U; col < COLS; col++) {
      if (row == col) {
        matrix[row][col] = 1;
      } else {
        matrix[row][col] = 0;
      }
    }
  }
}

Matrix3D::Matrix3D(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
  matrix[0][0] = m00;
  matrix[0][1] = m01;
  matrix[0][2] = m02;
  matrix[1][0] = m10;
  matrix[1][1] = m11;
  matrix[1][2] = m12;
  matrix[2][0] = m20;
  matrix[2][1] = m21;
  matrix[2][2] = m22;
}

Matrix3D Matrix3D::transpose() const {
  Matrix3D result;

  for (unsigned int row = 0U; row < ROWS; row++) {
    for (unsigned int col = 0U; col < COLS; col++) {
      result.matrix[row][col] = matrix[col][row];
    }
  }

  return result;
}

float Matrix3D::determinant() const {
  /*Using the formula for the determinant of a 3x3 matrix */
  float a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
  float d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
  float g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];

  return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

Matrix3D Matrix3D::inverse() const {
  Matrix3D result;

  /* Calculate determinant */
  float det = this->determinant();
  if (det == 0) {
    throw std::runtime_error("Matrix is singular and cannot be inverted!");
  }

  /* Using the adjugate matrix (Cofactor matrix transposed) */
  float a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
  float d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
  float g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];

  result.matrix[0][0] = (e * i - f * h) / det;
  result.matrix[0][1] = -(b * i - c * h) / det;
  result.matrix[0][2] = (b * f - c * e) / det;

  result.matrix[1][0] = -(d * i - f * g) / det;
  result.matrix[1][1] = (a * i - c * g) / det;
  result.matrix[1][2] = -(a * f - c * d) / det;

  result.matrix[2][0] = (d * h - e * g) / det;
  result.matrix[2][1] = -(a * h - b * g) / det;
  result.matrix[2][2] = (a * e - b * d) / det;

  return result;
}

void Matrix3D::orthonormalize() {
  /* Gram-Schmidt orthogonalization process */

  Vector3D xAxis(matrix[0][0], matrix[1][0], matrix[2][0]);
  Vector3D yAxis(matrix[0][1], matrix[1][1], matrix[2][1]);
  Vector3D zAxis(matrix[0][2], matrix[1][2], matrix[2][2]);

  /* Normalize the X axis */
  xAxis = xAxis.normalize();

  /* Make Y axis orthogonal to X axis */
  yAxis = yAxis - xAxis * xAxis.dotProduct(yAxis);
  yAxis = yAxis.normalize();

  /* Make Z axis orthogonal to X axis and Y axis */
  zAxis = zAxis - (xAxis * xAxis.dotProduct(zAxis)) - (yAxis * yAxis.dotProduct(zAxis));
  zAxis = zAxis.normalize();

  /* Rebuild matrix */
  matrix[0][0] = xAxis.x;
  matrix[0][1] = yAxis.x;
  matrix[0][2] = zAxis.x;
  matrix[1][0] = xAxis.y;
  matrix[1][1] = yAxis.y;
  matrix[1][2] = zAxis.y;
  matrix[2][0] = xAxis.z;
  matrix[2][1] = yAxis.z;
  matrix[2][2] = zAxis.z;
}

bool Matrix3D::isOrthonormal(float tolerance) const {
  Vector3D xAxis(matrix[0][0], matrix[1][0], matrix[2][0]);
  Vector3D yAxis(matrix[0][1], matrix[1][1], matrix[2][1]);
  Vector3D zAxis(matrix[0][2], matrix[1][2], matrix[2][2]);

  /* Check if axes are normalized (length ≈ 1) */
  if (std::abs(xAxis.lengthSquared() - 1.0f) > tolerance)
    return false;
  if (std::abs(yAxis.lengthSquared() - 1.0f) > tolerance)
    return false;
  if (std::abs(zAxis.lengthSquared() - 1.0f) > tolerance)
    return false;

  /* Check if axes are perpendicular (dot product ≈ 0) */
  if (std::abs(xAxis.dotProduct(yAxis)) > tolerance)
    return false;
  if (std::abs(yAxis.dotProduct(zAxis)) > tolerance)
    return false;
  if (std::abs(zAxis.dotProduct(xAxis)) > tolerance)
    return false;

  return true;
}
