#include "figure.h"

#include <math.h>

double squareArea(const double side)
{
  return rectangleArea(side, side);
}

double rectangleArea(const double a, const double b)
{
  return (a < 0 || b < 0) ? -1 : a * b;
}

double circleArea(const double radius)
{
  return radius < 0 ? -1 : radius * radius * M_PI;
}

double triangleArea(const double a, const double b, const double c)
{
  // Sanity check!
  if (a < 0 || b < 0 || c < 0) {
    return -1;
  }

  // Check triangle inequality.
  if (a + b <= c || a + c <= b || b + c <= a) {
    return -1;
  }

  const double p = 0.5 * (a + b + c);
  return sqrt(p * (p - a) * (p - b) * (p - c));
}