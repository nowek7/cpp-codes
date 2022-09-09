#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

unsigned char hexCharToInt(const char aChar)
{
  if (aChar >= '0' && aChar <= '9')
  {
    return aChar - '0';
  }

  if (aChar >= 'A' && aChar <= 'F')
  {
    return aChar - 'A' + 10;
  }

  if (aChar >= 'a' && aChar <= 'f')
  {
    return aChar - 'a' + 10;
  }

  throw std::invalid_argument("Invalid hexdecimal char!");
}

std::vector<unsigned char> hexStringToBytes(std::string_view aString)
{
  std::vector<unsigned char> output;
  for (auto i = 0; i < aString.size(); i += 2)
  {
    auto value = hexCharToInt(aString[i]) << 4;
    auto nextValue = hexCharToInt(aString[i + 1]);
    output.push_back(value | nextValue);
  }

  return output;
}

int main()
{
  std::vector<unsigned char> expected{0xBA, 0xAD, 0x42};

  {
    std::string text = "BAAD42";
    auto result = hexStringToBytes(text);

    std::cout << text << std::endl;
    std::cout << "Expected \t Result" << std::endl;
    if (expected.size() == result.size())
    {
      for (auto i = 0; i < result.size(); i++)
      {
        std::cout << expected[i] << " \t " << result[i] << std::endl;
      }
    }
  }

  {
    std::string text = "Baad42";
    auto result = hexStringToBytes(text);

    std::cout << text << std::endl;
    std::cout << "Expected \t Result" << std::endl;
    if (expected.size() == result.size())
    {
      for (auto i = 0; i < result.size(); i++)
      {
        std::cout << expected[i] << " \t " << result[i] << std::endl;
      }
    }
  }
}