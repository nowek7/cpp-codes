#include <iostream>
#include <optional>

constexpr double EPSILON = 0.0001;

struct Solution
  {
  double theValue;
  double theError;

  Solution(double &&aValue, double &&aError) noexcept
    {
    theValue = std::move(aValue);
    theError = std::move(aError);
    }
  };

double func(double &aValue)
  {
  return std::cos(aValue) - aValue;
  }

std::optional<Solution> falsiMethod(double &aLeftOfInterval, double &aRightEndOfInterval)
  {
  double error = 1;
  while (error > EPSILON)
    {
    // func'(x)=-sin(x) - 1 descending;
    // func''(x) = -cos(x) -> concave in that interval.
    auto length = aRightEndOfInterval - aLeftOfInterval;
    auto diffValue = func(aRightEndOfInterval) - func(aLeftOfInterval);
    aLeftOfInterval = -((func(aLeftOfInterval) * length) / diffValue) + aLeftOfInterval;

    error = std::abs(func(aLeftOfInterval) * 2);
    }

  return std::make_optional<Solution>(Solution(std::move(aLeftOfInterval), std::move(error)));
  }

int main()
  {
  std::cout << "Using falsi method to solve equation cos(x) = x in interval [0, pi/3]" << std::endl;
  std::cout << std::endl;

  double leftEndOfInterval = 0;
  double rightEndOfInterval = 1.0471;

  auto solution = falsiMethod(leftEndOfInterval, rightEndOfInterval);
  if (solution.has_value())
    {
    auto solutionValue = solution.value();
    std::cout << "Solution of equation -> " << solutionValue.theValue << std::endl;
    std::cout << "Error -> " << solutionValue.theError << std::endl;
    }
  else
    std::cout << "Something gone wrong!" << std::endl;

  solution.reset();

  return 0;
  }
