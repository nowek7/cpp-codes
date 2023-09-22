#ifndef FIGURE_H
#define FIGURE_H

#define NUM_FIGURES 4

enum Figures
{
  SQUARE = 1,
  RECTANGLE,
  CIRCLE,
  TRIANGLE
};

const char* shapeToStringGenitive[4] = {"kwadratu", "prostokata", "kola", "trojkata"};

const char* formulas[4] = {
  "a * a, gdzie a jest dlugoscia boku",
  "a * b, gdzie a i b sa dlugosciami boku",
  "r * r * pi, gdzie r jest promieniem kola, a stala pi = 3.14159265358979323846",
  "(p * (p - a) * (p - b) * (p - c)) ^ 0.5, gdzie a,b i c sa dlugosciami bokow trojkata i p = 0.5 * (a + b + c)"
};

double squareArea(const double side);
double rectangleArea(const double a, const double b);
double circleArea(const double radius);

// The Heron formula is used to compute the triangle area.
double triangleArea(const double a, const double b, const double c);

#endif // FIGURE_H