#pragma once

/*******************************************************************************************************************************
 * @file   math_utils.h
 *
 * @brief  Header file for the math utilities
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */
#include <cmath>

/* Inter-component Headers */

/* Intra-component Headers */
#include "vector_3d.h"

/**
 * @defgroup CoreModules
 * @brief    Core modules to run on the CPU for physics management
 * @{
 */

namespace math {
constexpr float PI = 3.14159265358979323846f;
constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;
constexpr float EPSILON = 1e-6f;

float clamp(float value, float min, float max);
float lerp(float startValue, float endValue, float t);
float smoothStep(float edge0, float edge1, float x);

float distance(const Vector3D &a, const Vector3D &b);
float angle(const Vector3D &a, const Vector3D &b);
Vector3D projectOnPlane(const Vector3D &vector, const Vector3D &normal);
}  // namespace math

/** @} */
