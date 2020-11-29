#include <iostream>
#include <cmath>

struct ComplexNumber
  {
  public:
    double theRealNumber = 0;
    double theImiginaryNumber = 0;

    ComplexNumber() = default;
    ComplexNumber(const double &aRealNumber, const double aImiginaryNumber = 0);
    ComplexNumber(const ComplexNumber &aComplexNumber);
    ComplexNumber(ComplexNumber &&aComplexNumber);

    ComplexNumber operator+(const ComplexNumber &aOther);
    ComplexNumber operator+(const double &aOther);

    ComplexNumber operator-(const ComplexNumber &aOther);
    ComplexNumber operator-(const double &aOther);

    ComplexNumber operator*(const ComplexNumber &aOther);
    ComplexNumber operator*(const double &aOther);

    ComplexNumber operator/(const ComplexNumber &aDivisor);
    ComplexNumber operator/(const double &aDivisor);

    bool operator==(const ComplexNumber &aOther);
    bool operator!=(const ComplexNumber &aOther);

    friend ComplexNumber conjugate(const ComplexNumber &aComplexNumber);

    friend std::ostream &operator<<(std::ostream &aOstream, const ComplexNumber &aComplexNumber);
    friend double absolute(const ComplexNumber &aComplexNumber);
  };

ComplexNumber::ComplexNumber(const double &aRealNumber, const double aImiginaryNumber)
  :
  theRealNumber(aRealNumber),
  theImiginaryNumber(aImiginaryNumber)
  {}

ComplexNumber::ComplexNumber(const ComplexNumber &aComplexNumber)
  :
  theRealNumber(aComplexNumber.theRealNumber),
  theImiginaryNumber(aComplexNumber.theImiginaryNumber)
  {}

ComplexNumber::ComplexNumber(ComplexNumber &&aComplexNumber)
  :
  theRealNumber(std::move(aComplexNumber.theRealNumber)),
  theImiginaryNumber(std::move(aComplexNumber.theImiginaryNumber))
  {}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &aOther)
  {
  double real = theRealNumber + aOther.theRealNumber;
  double imiginary = theRealNumber + aOther.theImiginaryNumber;

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator+(const double &aOther)
  {
  double real = theRealNumber + aOther;
  return ComplexNumber(real, theImiginaryNumber);
  }

ComplexNumber ComplexNumber::operator-(const ComplexNumber &aOther)
  {
  double real = theRealNumber - aOther.theRealNumber;
  double imiginary = theRealNumber - aOther.theImiginaryNumber;

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator-(const double &aOther)
  {
  double real = theRealNumber - aOther;

  return ComplexNumber(real, theImiginaryNumber);
  }

ComplexNumber ComplexNumber::operator*(const ComplexNumber &aOther)
  {
  double real = (aOther.theRealNumber * theRealNumber) - (aOther.theImiginaryNumber * theImiginaryNumber);
  double imiginary = (aOther.theImiginaryNumber * theRealNumber) + (aOther.theRealNumber * theImiginaryNumber);

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator*(const double &aOther)
  {
  const double real = theRealNumber * aOther;
  const double imiginary = theImiginaryNumber * aOther;

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator/(const ComplexNumber &aDivisor)
  {
  if ((aDivisor.theRealNumber == 0) && (aDivisor.theImiginaryNumber == 0))
    throw std::logic_error("Cannot divide by zero!");

  const double denominator = (aDivisor.theRealNumber * aDivisor.theRealNumber) + (aDivisor.theImiginaryNumber * aDivisor.theImiginaryNumber);

  const double real = ((theRealNumber * aDivisor.theRealNumber) - (theImiginaryNumber * aDivisor.theImiginaryNumber)) / denominator;
  const double imiginary = ((theRealNumber * aDivisor.theImiginaryNumber) + (theImiginaryNumber * aDivisor.theRealNumber)) / denominator;

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator/(const double &aDivisor)
  {
  if (aDivisor == 0)
    throw std::logic_error("Cannot divide by zero!");

  double real = theRealNumber / aDivisor;
  double imiginary = theImiginaryNumber / aDivisor;

  return ComplexNumber(real, imiginary);
  }

bool ComplexNumber::operator==(const ComplexNumber &aOther)
  {
  return (theRealNumber == aOther.theRealNumber) && (theImiginaryNumber == aOther.theImiginaryNumber);
  }

bool ComplexNumber::operator!=(const ComplexNumber &aOther)
  {
  return !(*this == aOther);
  }

std::ostream &operator<<(std::ostream &aOstream, const ComplexNumber &aComplexNumber)
  {
  if (aComplexNumber.theImiginaryNumber > 0)
    return aOstream << aComplexNumber.theRealNumber << " + " << aComplexNumber.theImiginaryNumber << "i";
  else if (aComplexNumber.theImiginaryNumber == 0)
    return aOstream << aComplexNumber.theRealNumber;
  else
    return aOstream << aComplexNumber.theRealNumber << " - " << -aComplexNumber.theImiginaryNumber << "i";
  }

ComplexNumber conjugate(ComplexNumber &aComplexNumber)
  {
  return ComplexNumber(aComplexNumber.theRealNumber, -aComplexNumber.theImiginaryNumber);
  }

double absolute(const ComplexNumber &aComplexNumber)
  {
  return std::sqrt((aComplexNumber.theRealNumber * aComplexNumber.theRealNumber) + (aComplexNumber.theImiginaryNumber * aComplexNumber.theImiginaryNumber));
  }

int main()
  {
  ComplexNumber xNumber{1, 10};
  ComplexNumber yNumber{-10.5, -1};

  std::cout << "x + y = " << xNumber + yNumber << std::endl;
  std::cout << "x - y = " << xNumber - yNumber << std::endl;
  std::cout << "x * y = " << xNumber * yNumber << std::endl;
  std::cout << "x / y = " << xNumber / yNumber << std::endl;
  std::cout << "|x| = " << absolute(xNumber) << std::endl;
  std::cout << "|y| = " << absolute(yNumber) << std::endl;
  std::cout << conjugate(xNumber) << std::endl;
  std::cout << conjugate(yNumber) << std::endl;

  return 0;
  }
