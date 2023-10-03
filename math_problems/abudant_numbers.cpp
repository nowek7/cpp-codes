#include <cmath>
#include <iostream>
#include <set>

namespace {
  constexpr int LIMIT = 100;
} // namespace

int sumProperDivisors(int number)
{
  int result = 1;
  for (int i = 2; i <= std::sqrt(number); ++i) {
    if (number % i == 0) {
      result += (i == (number / i)) ? i : (i + number / i);
    }
  }

  return result;
}

void printAbudantNumber(int limit)
{
  std::cout << "Number"
            << "\t"
            << "Sum of proper divisor" << std::endl;

  for (int number = 4; number < limit; ++number) {
    const auto sum = sumProperDivisors(number);
    if (sum > number) {
      std::cout << number << '\t' << sum << '\n';
    }
  }
}

int main()
{
  printAbudantNumber(LIMIT);
}