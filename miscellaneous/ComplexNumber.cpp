#include <iostream>
#include <cmath>

struct ComplexNumber
  {
  public:
    double theRealNumber = 0;
    double theImiginaryNumber = 0;

    ComplexNumber() = default;
    ComplexNumber(double &aRealNumber, double aImiginaryNumber = 0);
    ComplexNumber(const ComplexNumber &aComplexNumber);

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

ComplexNumber::ComplexNumber(double &aRealNumber, double aImiginaryNumber)
  :
  theRealNumber(aRealNumber),
  theImiginaryNumber(aImiginaryNumber)
  {}

ComplexNumber::ComplexNumber(const ComplexNumber &aComplexNumber)
  :
  theRealNumber(aComplexNumber.theRealNumber),
  theImiginaryNumber(aComplexNumber.theImiginaryNumber)
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
  double real = theRealNumber * aOther;
  double imiginary = theImiginaryNumber * aOther;

  return ComplexNumber(real, imiginary);
  }

ComplexNumber ComplexNumber::operator/(const ComplexNumber &aDivisor)
  {
  if ((aDivisor.theRealNumber == 0) && (aDivisor.theImiginaryNumber == 0))
    throw std::logic_error("Cannot divide by zero!");

  double denominator = (aDivisor.theRealNumber * aDivisor.theRealNumber) + (aDivisor.theImiginaryNumber * aDivisor.theImiginaryNumber);

  double real = ((theRealNumber * aDivisor.theRealNumber) - (theImiginaryNumber * aDivisor.theImiginaryNumber)) / denominator;
  double imiginary = ((theRealNumber * aDivisor.theImiginaryNumber) + (theImiginaryNumber * aDivisor.theRealNumber)) / denominator;

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
  return (theRealNumber != aOther.theRealNumber) && (theImiginaryNumber != aOther.theImiginaryNumber);
  }

std::ostream &operator<<(std::ostream &aOstream, const ComplexNumber &aComplexNumber)
  {
  if (aComplexNumber.theImiginaryNumber > 0)
    return aOstream << aComplexNumber.theRealNumber << " + " << aComplexNumber.theImiginaryNumber << "i";
  else if (aComplexNumber.theImiginaryNumber == 0)
    return aOstream << aComplexNumber.theRealNumber;
  else
    return aOstream << aComplexNumber.theRealNumber << " " << aComplexNumber.theImiginaryNumber << "i";
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
  ComplexNumber xNumber;
  ComplexNumber yNumber;

  std::cout << "Input first number:" << std::endl;
  std::cout << "Re: ";
  std::cin >> xNumber.theRealNumber;
  std::cout << "Im: ";
  std::cin >> xNumber.theImiginaryNumber;
  std::cout << "============================="<< std::endl;

  std::cout << "Input second number:" << std::endl;
  std::cout << "Re: ";
  std::cin >> yNumber.theRealNumber;
  std::cout << "Im: ";
  std::cin >> yNumber.theImiginaryNumber;
  std::cout << "=============================" << std::endl;

  std::cout << "First number: " << xNumber << std::endl;
  std::cout << "Second number: " << yNumber << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << std::endl;
  std::cout << "======== Complex numbers calculator ========" << std::endl;
  std::cout << "1. Adding." << std::endl;
  std::cout << "2. Substraction." << std::endl;
  std::cout << "3. Multiplication." << std::endl;
  std::cout << "4. Divide." << std::endl;
  std::cout << "5. Absolute value." << std::endl;
  std::cout << "6. Conjugate." << std::endl;
  std::cout << "100. Exit." << std::endl;
  std::cout << "=============================" << std::endl;

  bool doFinish = false;
  while (!doFinish)
    {
    int choose;
    std::cout << "Input function number: ";
    std::cin >> choose;
    switch (choose)
      {
      case 1:
        std::cout << xNumber + yNumber << std::endl;
        break;

      case 2:
        std::cout << xNumber - yNumber << std::endl;
        break;

      case 3:
        std::cout << xNumber * yNumber << std::endl;
        break;

      case 4:
        std::cout << xNumber / yNumber << std::endl;
        break;

      case 5:
        std::cout << "|" << xNumber << "| = " << absolute(xNumber) << std::endl;
        std::cout << "|" << yNumber << "| = " << absolute(yNumber) << std::endl;
        break;

      case 6:
        std::cout << conjugate(xNumber) << std::endl;
        std::cout << conjugate(yNumber) << std::endl;
        break;

      case 100:
        doFinish = true;
        std::cout << "Goodbye!" << std::endl;
        break;

      default:
        std::cout << "Error. Lack option in calculator!" << std::endl;
        break;
      }

    std::cout << "=============================" << std::endl;
    }

  return 0;
  }
