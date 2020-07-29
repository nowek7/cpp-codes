#include <iostream>

bool isPrime(const int &aNumber)
  {
  if (aNumber <= 3)
    return aNumber > 1;
  else if ((aNumber % 2 == 0) || (aNumber % 3 == 0))
    return false;
  else
    {
    for (int i = 5; i * i < aNumber; i += 6)
      {
      if ((aNumber % i == 0) || (aNumber % (i + 2) == 0))
        return false;
      }

    return true;
    }
  }

int main()
  {
  const int limit = 15;

  for (int i = limit; i > 1; i--)
    {
    if (isPrime(i))
      {
      std::cout << "Largest prime is -> " << i << std::endl;

      return 0;
      }
    }
  }