#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<unsigned int, char const*>> ROMANS_NUMBER{ {1000, "M"},
                                                                 {900, "CM"},
                                                                 {500, "D"},
                                                                 {400, "CD"},
                                                                 {100, "C"},
                                                                 {90, "XC"},
                                                                 {50, "L"},
                                                                 {40, "XL"},
                                                                 {10, "X"},
                                                                 {9, "IX"},
                                                                 {5, "V"},
                                                                 {4, "IV"},
                                                                 {1, "I"} };

std::string numberToRoman(unsigned int value)
{
  std::string result;
  for (auto const& pair: ROMANS_NUMBER)
  {
    while (value >= pair.first)
    {
      result += pair.second;
      value -= pair.first;
    }
  }

  return result;
}

int main()
{
  for (auto i = 1; i <= 2020; i++)
    std::cout << i << " -> " << numberToRoman(i) << std::endl;
}