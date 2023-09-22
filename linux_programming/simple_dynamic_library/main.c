#include "figure/figure.h"

#include <stdio.h>

void printLabel(const int* shapeIdx)
{
  if (*shapeIdx > 0 && *shapeIdx <= NUM_FIGURES) {
    printf("Wybrales pole %s. Wzor na pole %s to %s.\n",
           shapeToStringGenitive[*shapeIdx - 1],
           shapeToStringGenitive[*shapeIdx - 1],
           formulas[*shapeIdx - 1]);
  }
}

int main()
{
  printf("\t\tPROGRAM OBLICZAJACY POLA FIGUR\t\t\n");
  printf("*******************************\n");
  printf("Jakiej figury pole chcialbys policzyc?\n");
  printf("1. Kwadrat \n2. Prostokat \n3. Kolo \n4. Trojkat \n");
  printf("*******************************\n");

  int choose;
  printf("Wybieram -> ");
  scanf("%d", &choose);

  printLabel(&choose);

  double area = 0;
  switch (choose) {
    case SQUARE: {
      double side;
      printf("********KWADRAT********\n");
      printf("Bok a -> ");
      scanf("%lf", &side);

      area = squareArea(side);

      break;
    }

    case RECTANGLE: {
      double a, b;
      printf("********PROSTOKAT********\n");

      printf("Bok a -> ");
      scanf("%lf", &a);
      printf("Bok b -> ");
      scanf("%lf", &b);

      area = rectangleArea(a, b);

      break;
    }

    case CIRCLE: {
      double radius;

      printf("********KOLO********\n");
      printf("Promien -> ");
      scanf("%lf", &radius);

      area = circleArea(radius);

      break;
    }

    case TRIANGLE: {
      double a, b, c;

      printf("********TROJKAT********\n");
      printf("Podaj dlugosc boku a: ");
      scanf("%lf", &a);
      printf("Podaj dlugosc boku b: ");
      scanf("%lf", &b);
      printf("Podaj dlugosc boku c: ");
      scanf("%lf", &c);

      area = triangleArea(a, b, c);

      break;
    }

    default: {
      printf("Nieznany ksztalt! Program liczy tylko pole powierzchni ponizszych ksztaltow:\n");
      printf("1. Kwadrat \t 2. Prostokat \t 3. Kolo \t 4. Trojkat \n");
      return 0;
    }
  }

  printf("\n");

  if (area < 0) {
    printf("Zostaly podane niepoprawne dane!\n");
  } else {
    printf("Pole: %0.3lf\n", area);
  }

  return 0;
}