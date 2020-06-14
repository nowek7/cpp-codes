#include <iostream>

int main()
  {
  auto isPrime = [](const int aNumber)
    {
    if (aNumber < 2)
      return false;

    if (aNumber <= 3)
      return true;

    for (int i = 2; i * i <= aNumber; i++)
      {
      if (aNumber % i == 0)
        return false;
      }

    return true;
    };

  for (auto i = 0; i < 100'000; i++)
    {
    if (isPrime(i))
      std::cout << i << " is prime number." << std::endl;
    }
  }