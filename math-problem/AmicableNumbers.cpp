#include <cmath>
#include <iostream>
#include <set>

constexpr int LIMIT = 1'000'000;

int sumProperDivisors(int const number)
  {
  int result = 1;
  for (int i = 2; i <= std::sqrt(number); i++)
    {
    if (number % i == 0)
      result += (i == (number / i)) ? i : (i + number / i);
    }

  return result;
  }

void printAmicables(int const limit)
  {
  for (int number = 4; number < limit; ++number)
    {
    auto sum1 = sumProperDivisors(number);

    if (sum1 < limit)
      {
      auto sum2 = sumProperDivisors(sum1);

      if ((sum2 == number) && (number != sum1))
        std::cout << number << "\t" << sum1 << std::endl;
      }
    }
  }

void printAmicablesOnce(int const limit)
  {
  std::set<int> printed;
  for (int number = 4; number < limit; ++number)
    {
    if (printed.find(number) != printed.end())
      continue;

    auto sum1 = sumProperDivisors(number);
    if (sum1 < limit)
      {
      auto sum2 = sumProperDivisors(sum1);
      if (sum2 == number && number != sum1)
        {
        printed.insert(number);
        printed.insert(sum1);

        std::cout << number << "\t" << sum1 << std::endl;
        }
      }
    }
  }

int main()
  {
  printAmicables(LIMIT);
  std::cout << "--------------" << std::endl;
  printAmicablesOnce(LIMIT);
  }
