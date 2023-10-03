#include <cmath>
#include <iostream>

template<typename Arithmetic>
Arithmetic max(const Arithmetic a, const Arithmetic b, const Arithmetic c)
{
  if (a > b) {
    if (a > c) {
      return a;
    } else {
      return c;
    }
  } else {
    if (b > c) {
      return b;
    } else {
      return c;
    }
  }
}

struct Complex
{
  int re;
  int im;

  friend double abs(const Complex number)
  {
    return std::sqrt((number.re * number.re) + (number.im * number.im));
  }

  friend std::ostream& operator<<(std::ostream& os, const Complex number)
  {
    os << number.re << " + " << number.im << "i";
    return os;
  }

  friend bool operator>(const Complex& lhs, const Complex& rhs)
  {
    return abs(lhs) > abs(rhs);
  }

  friend bool operator<(const Complex& lhs, const Complex& rhs)
  {
    return !(lhs > rhs);
  }
};

int main()
{
  int a = 10;
  int b = 9;
  int c = 15;
  std::cout << "max(" << a << ", " << b << ", " << c << ") = " << max(a, b, c) << std::endl;

  Complex complA;
  complA.re = 10;
  complA.im = 0;

  Complex complB;
  complB.re = 9;
  complB.im = 100;

  Complex complC;
  complC.re = 15;
  complC.im = 10;

  std::cout << "max(a, b, c)= " << max(complA, complB, complC) << std::endl;

  return 0;
}