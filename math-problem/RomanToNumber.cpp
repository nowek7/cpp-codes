#include <iostream>
#include <string>
#include <unordered_map>

unsigned int romanToNumber(std::string roman)
  {
  std::unordered_map<char, unsigned int> ROMAN_NUMBERS
    {
      { 'M', 1000 }, { 'D', 500 }, { 'C', 100 }, { 'L', 50 }, { 'X', 10 }, { 'IX', 9 }, { 'V', 5 }, { 'I', 1 }
    };

  unsigned int result = ROMAN_NUMBERS[roman.back()];
  for (int i = roman.size() - 2; i >= 0; i--)
    {
    if (ROMAN_NUMBERS[roman[i]] >= ROMAN_NUMBERS[roman[i + 1]])
      result += ROMAN_NUMBERS[roman[i]];
    else
      result -= ROMAN_NUMBERS[roman[i]];
    }

  return result;
  }

int main()
  {
  std::cout << "I = " << romanToNumber("I") << std::endl;
  std::cout << "III = " << romanToNumber("III") << std::endl;
  std::cout << "IV = " << romanToNumber("IV") << std::endl;
  std::cout << "XI = " << romanToNumber("XI") << std::endl;
  std::cout << "XX = " << romanToNumber("XX") << std::endl;
  std::cout << "XXV = " << romanToNumber("XXV") << std::endl;
  std::cout << "MCMXCIX = " << romanToNumber("MCMXCIX") << std::endl;
  std::cout << "M = " << romanToNumber("M") << std::endl;
  }