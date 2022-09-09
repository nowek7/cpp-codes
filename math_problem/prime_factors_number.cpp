#include <iostream>
#include <iterator>
#include <vector>

std::vector<unsigned long long> computerPrimeFractors(unsigned long long aNumber)
{
  auto primeFactors = std::vector<unsigned long long>{};

  while (aNumber % 2 == 0)
  {
    primeFactors.push_back(2);
    aNumber /= 2;
  }

  for (unsigned long long i = 3; i * i <= aNumber; i += 2)
  {
    while (aNumber % i == 0)
    {
      primeFactors.push_back(i);
      aNumber /= i;
    }
  }

  // Number is prime number.
  if (aNumber > 2)
  {
    primeFactors.push_back(aNumber);
  }

  return primeFactors;
}

int main()
{
  unsigned long long number = 1500;

  auto factors = computerPrimeFractors(number);

  std::copy(std::begin(factors), std::end(factors), std::ostream_iterator<unsigned long long>(std::cout, " "));
  std::cout << std::endl;
}