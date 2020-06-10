#include <iostream>

int main()
  {
  auto nthCollatzNumber = [](unsigned int const aNumber, unsigned const int N)
    {
    auto number = aNumber;
    for (auto i = 0; i < N && number != 1; i++)
      {
      if (number % 2 == 0)
        number *= 0.5;
      else
        number = 3 * number + 1;
      }
    return number;
    };

  int n = 20;
  std::cout << n << "th Collatz number -> " << nthCollatzNumber(11, n) << std::endl;
  }