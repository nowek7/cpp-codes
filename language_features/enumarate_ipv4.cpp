#include <array>
#include <assert.h>
#include <iostream>
#include <sstream>

class IPv4
{
private:
  std::array<unsigned char, 4> theData;

public:
  constexpr IPv4():
    theData{{0}}
  {
  }

  constexpr IPv4(unsigned char aPart0,
                 unsigned char aPart1,
                 unsigned char aPart2,
                 unsigned char aPart3):
    theData{{ aPart0, aPart1, aPart2, aPart3 }}
  {
  }

  explicit constexpr IPv4(unsigned long aData):
    theData{ {static_cast<unsigned char>((aData >> 24) & 0xFF),
              static_cast<unsigned char>((aData >> 16) & 0xFF),
              static_cast<unsigned char>((aData >> 8) & 0xFF),
              static_cast<unsigned char>((aData & 0xFF)) }}
  {
  }

  // Copy constructor
  IPv4(const IPv4& aOther) noexcept
  {
    theData = aOther.getData();
  }

  IPv4& operator=(const IPv4& aOther) noexcept
  {
    theData = aOther.getData();
    return *this;
  }

  std::string toString() const
  {
    std::stringstream stream;
    stream << *this;
    return stream.str();
  }

  constexpr bool isLoopback() const noexcept
  {
    return (toUlong() & 0xFF000000) == 0x7F000000;
  }

  constexpr bool isUnspecified() const noexcept
  {
    return toUlong() == 0;
  }

  constexpr bool isClassA() const noexcept
  {
    return (toUlong() & 0x80000000) == 0;
  }

  constexpr bool isClassB() const noexcept
  {
    return (toUlong() & 0xC0000000) == 0x80000000;
  }

  constexpr bool isClassC() const noexcept
  {
    return (toUlong() & 0xE0000000) == 0xC0000000;
  }

  constexpr bool isMulticast() const noexcept
  {
    return (toUlong() & 0xF0000000) == 0xE0000000;
  }

  constexpr unsigned long toUlong() const noexcept
  {
    return (static_cast<unsigned long>(theData[0]) << 24) | (static_cast<unsigned long>(theData[1]) << 16) |
           (static_cast<unsigned long>(theData[2]) << 8) | (static_cast<unsigned long>(theData[3]));
  }

  void setData(std::array<unsigned char, 4>& aData)
  {
    theData = aData;
  }

  std::array<unsigned char, 4> getData() const
  {
    return theData;
  }

  // Prefix
  IPv4& operator++()
  {
    *this = IPv4(1 + toUlong());
    return *this;
  }

  // Postfix
  IPv4& operator++(int)
  {
    IPv4 result(*this);
    ++(*this);
    return *this;
  }

  friend bool operator==(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return aLeft.getData() == aRight.getData();
  }

  friend bool operator!=(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return !(aLeft == aRight);
  }

  friend bool operator<(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return aLeft.toUlong() < aRight.toUlong();
  }

  friend bool operator>(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return aRight < aLeft;
  }

  friend bool operator<=(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return !(aLeft > aRight);
  }

  friend bool operator>=(const IPv4& aLeft, const IPv4& aRight) noexcept
  {
    return !(aLeft < aRight);
  }

  friend std::ostream& operator<<(std::ostream& aOstream, const IPv4& aAddress)
  {
    const auto data = aAddress.getData();
    aOstream << static_cast<int>(data[0]) << "." << static_cast<int>(data[1]) << "." << static_cast<int>(data[2]) << "."
             << static_cast<int>(data[3]);

    return aOstream;
  }

  friend std::istream& operator>>(std::istream& stream, IPv4& aAddress)
  {
    char data1, data2, data3;
    int bit1, bit2, bit3, bit4;

    stream >> bit1 >> data1 >> bit2 >> data2 >> bit3 >> data3 >> bit4;
    if ((data1 == '.') && (data2 == '.') && (data3 == '.'))
    {
      aAddress = IPv4(bit1, bit2, bit3, bit4);
    }
    else
    {
      stream.setstate(std::ios::failbit);
    }

    return stream;
  }
};

int main()
{
  std::cout << "input range: ";
  IPv4 ipv4_1, ipv4_2;
  std::cin >> ipv4_1 >> ipv4_2;
  if (ipv4_2 > ipv4_1)
  {
    for (IPv4 ipv4 = ipv4_1; ipv4 <= ipv4_2; ipv4++)
    {
      std::cout << ipv4 << std::endl;
    }
  }
  else
  {
    std::cerr << "invalid range!" << std::endl;
  }

  return 0;
}