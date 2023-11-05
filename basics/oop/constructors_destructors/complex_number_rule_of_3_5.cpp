#include <cmath>
#include <iostream>

struct ComplexNumber
{
public:
  ComplexNumber() = default;
  ComplexNumber(double real, double imiginary = 0);
  ComplexNumber(const ComplexNumber& other);
  ComplexNumber(ComplexNumber&& other);

  ComplexNumber& operator=(const ComplexNumber& other);
  ComplexNumber& operator=(ComplexNumber&& other);

  ~ComplexNumber() = default;

private:
  double theReal;
  double theImiginary;
};

ComplexNumber::ComplexNumber(double real, double imiginary):
  theReal(real),
  theImiginary(imiginary)
{
}

ComplexNumber::ComplexNumber(const ComplexNumber& other):
  theReal(other.theReal),
  theImiginary(other.theImiginary)
{
}

ComplexNumber::ComplexNumber(ComplexNumber&& other):
  theReal(std::move(other.theReal)),
  theImiginary(std::move(other.theImiginary))
{
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& other)
{
  theReal = other.theReal;
  theImiginary = other.theImiginary;
  return *this;
}

ComplexNumber& ComplexNumber::operator=(ComplexNumber&& other)
{
  theReal = std::move(other.theReal);
  theImiginary = std::move(other.theImiginary);
  return *this;
}

int main()
{
  {
    ComplexNumber x {1, 10};
    ComplexNumber y = x;
  }

  {
    ComplexNumber x {100, 0};
    ComplexNumber y = std::move(x);
  }

  {
    ComplexNumber x {-1, -1};
    ComplexNumber y {0, 0};
    y = x;
  }

  {
    ComplexNumber x {-1, -1};
    ComplexNumber y {0, 0};
    y = std::move(x);
  }

  return 0;
}
