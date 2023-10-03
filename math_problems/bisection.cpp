#include <cmath>
#include <cstdlib>
#include <iostream>

constexpr int DIVIDE_COUNT = 5;
constexpr int SHIFT_VALUE = 5;

int main()
{
  std::cout << "Find root of equation: x*x - 5 = 0 in interval [0, 10]." << '\n';
  std::cout << '\n';

  auto equation = [](double aX) -> double {
    return (aX * aX) - SHIFT_VALUE;
  };

  const double leftOfInterval = 0;
  const double rightOfInterval = 10;
  for (int i = 0; i < DIVIDE_COUNT; i++) {
    const double root = (leftOfInterval + rightOfInterval) * 0.5;
    if (equation(root) == 0) {
      break;
    }

    if (equation(root) * equation(leftOfInterval) < 0) {
      rightOfInterval = root;
    } else if (equation(root) * equation(rightOfInterval) < 0) {
      leftOfInterval = root;
    }
  }

  std::cout << "Solution of equation -> " << root << '\n';
  std::cout << "Error -> " << std::abs(std::sqrt(5) - root) << '\n';

  return 0;
}
