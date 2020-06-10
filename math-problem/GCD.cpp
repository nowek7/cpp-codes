#include <iostream>

unsigned int gcd2(unsigned int const a, unsigned int const b)
  {
  return b == 0 ? a : gcd2(b, a % b);
  }

int main()
  {
  auto gcd1 = [](unsigned int a, unsigned int b)
    {
    if (b == 0)
      return a;

    while (a != b)
      {
      if (a < b)
        b -= a;
      else
        a -= b;
      }

    return a;
    };

  auto gcd3 = [](unsigned int a, unsigned int b)
    {
    while (b != 0)
      {
      unsigned int r = a % b;
      a = b;
      b = r;
      }

    return a;
    };

  int a = 7;
  int b = 13;

  std::cout << "gcd(" << a << ", " << b << ") = " << gcd1(a, b) << std::endl;
  std::cout << "gcd(" << a << ", " << b << ") = " << gcd2(a, b) << std::endl;
  std::cout << "gcd(" << a << ", " << b << ") = " << gcd3(a, b) << std::endl;
  }