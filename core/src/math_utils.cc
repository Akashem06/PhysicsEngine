/*******************************************************************************************************************************
 * @file   math_utils.cc
 *
 * @brief  Source file for the math utilities
 *
 * @date   2024-12-27
 * @author Aryan Kashem
 *******************************************************************************************************************************/

/* Standard library Headers */

/* Inter-component Headers */

/* Intra-component Headers */
#include "math_utils.h"

float clamp(float value, float min, float max) {
  if (value >= max) {
    return max;
  } else if (value <= min) {
    return min;
  } else {
    return value;
  }
}

float lerp(float startValue, float endValue, float t) {
  return (endValue - startValue) * t + startValue;
}

float smoothStep(float edge0, float edge1, float x) {
  return (x - edge0) / (x + edge1);
}
