#include <iostream>

bool isPrime(int aNumber)
{
  if (aNumber <= 3) {
    return aNumber > 1;
  } else if ((aNumber % 2 == 0) || (aNumber % 3 == 0)) {
    return false;
  } else {
    for (int i = 5; i * i < aNumber; i += 6) {
      if ((aNumber % i == 0) || (aNumber % (i + 2) == 0)) {
        return false;
      }
    }

    return true;
  }
}

int main()
{
  const int limit = 1500;

  std::cout << "Sexy prime numbers" << std::endl;
  std::cout << "n\tn + 6" << std::endl;
  for (int i = 2; i <= limit; i++) {
    if (isPrime(i) && isPrime(i + 6)) {
      std::cout << i << "\t" << i + 6 << std::endl;
    }
  }
}