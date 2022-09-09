#include <cmath>
#include <iomanip>
#include <iostream>

void printPascalTriangle(int aLevel)
{
  if (aLevel > 10)
  {
    std::cout << "Level to high!" << std::endl;
    return;
  }

  auto numberOfDigits = [](int aNumber)
  {
    return aNumber > 1 ? static_cast<int>(log10(static_cast<double>(aNumber))) + 1 : 1;
  };

  for (int i = 0; i < aLevel; i++)
  {
    int number = 1;
    std::cout << std::string((aLevel - i - 1) * (aLevel * 0.5), ' ');
    for (int j = 0; j <= i; j++)
    {
      int y = number;
      number = number * (i - j) / (j + 1);

      auto maxlen = numberOfDigits(number) - 1;
      std::cout << y << std::string(aLevel - 1 - maxlen - aLevel % 2, ' ');
    }

    std::cout << std::endl;
  }
}

int main()
{
  printPascalTriangle(10);

  return 0;
}