#include <bitset>
#include <iostream>
#include <string>

unsigned int grayEncode(unsigned int number)
{
  return number ^ (number >> 1);
}

unsigned int grayDecode(unsigned int gray)
{
  for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1)
  {
    if (gray & bit)
    {
      gray ^= bit >> 1;
    }
  }

  return gray;
}

std::string toBinary(unsigned int value, int digits)
{
  return std::bitset<32>(value).to_string().substr(32 - digits, digits);
}

int main()
{
  std::cout << "Number\tBinary\tGray\tDecoded\n";
  std::cout << "------\t------\t----\t-------\n";

  for (unsigned int num = 0; num < 32; ++num)
  {
    auto encodeGray = grayEncode(num);
    auto decodeGray = grayDecode(encodeGray);

    std::cout << num << "\t" << toBinary(num, 5)
                     << "\t" << toBinary(encodeGray, 5)
                     << "\t" << decodeGray
                     << "\n";
  }
}
