#include <iostream>
#include <cmath>

// O(sqrt(N))
auto isPerfect(const int &aNumber) -> bool
  {
  if (aNumber <= 0)
    return false;
  else
    {
    auto sum = int{0};
    for (auto i = 1; i * i < aNumber; ++i)
      {
      if (aNumber % i == 0)
        {
        sum += i;

        if (i * i != aNumber)
          sum += aNumber / i;
        }
      }
    return sum - aNumber == aNumber;
    }
  }

// Using Euclid theorem -  O(log(N))
auto isPerfectUsingEuclidTheorem(const int &aNumber) -> bool
  {
  // 2^(p - 1) * (2^(p) - 1)
  // Use mersenne primes number.
  if (aNumber <= 0)
    return false;
  else
    {
    int primes[8]{2, 3, 5, 7, 13, 17, 19, 31};
    for (int i = 0; i < 8; i++)
      {
      int number = std::pow(2, primes[i] - 1) * (std::pow(2, primes[i]) - 1);
      if (number == aNumber)
        return true;
      }

    return false;
    }
  }

int main()
  {
  for (auto i = 1; i < 10'000; i++)
    {
    if (isPerfectUsingEuclidTheorem(i))
      std::cout << i << std::endl;
    }

  return 0;
  }