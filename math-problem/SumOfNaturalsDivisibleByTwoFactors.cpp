#include <iostream>

constexpr int LIMIT = 10;
constexpr int FACTOR_ONE = 3;
constexpr int FACTOR_TWO = 5;

int main()
  {
  auto sum = []()
    {
    auto result = int{0};
    for (int i = 1; i < LIMIT; ++i)
      {
      if (i % 3 == 0 || i % 5 == 0)
        result += i;
      }

    return result;
    };

  std::cout << "Sum of naturals divisible by two factors: " << sum() << std::endl;
  }