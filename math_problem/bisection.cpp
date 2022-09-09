#include <cmath>
#include <cstdlib>
#include <iostream>

constexpr int DIVIDE_COUNT = 5;

int main()
{
  std::cout << "Find root of equation: x*x - 5 = 0 in interval [0, 10]." << std::endl;
  std::cout << std::endl;

  auto equation = [](double aX)
  {
    return (aX * aX) - 5;
  };

  double leftOfInterval = 0;
  double rightOfInterval = 10;
  double root;
  for (int i = 0; i < DIVIDE_COUNT; i++)
  {
    root = (leftOfInterval + rightOfInterval) * 0.5;
    if (equation(root) == 0)
    {
      break;
    }

    if (equation(root) * equation(leftOfInterval) < 0)
    {
      rightOfInterval = root;
    }
    else if (equation(root) * equation(rightOfInterval) < 0)
    {
      leftOfInterval = root;
    }
  }

  std::cout << "Solution of equation -> " << root << std::endl;
  std::cout << "Error -> " << std::abs(std::sqrt(5) - root) << std::endl;

  return 0;
}