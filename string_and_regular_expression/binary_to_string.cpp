#include <array>
#include <assert.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

template<typename Iterator>
std::string bytesToHexString(Iterator aBegin, Iterator aEnd, bool aUppercase = false)
{
  std::ostringstream osStream;
  if (aUppercase)
  {
    osStream.setf(std::ios_base::uppercase);
  }

  for (; aBegin != aEnd; ++aBegin)
  {
    osStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*aBegin);
  }

  return osStream.str();
}

template<typename C>
std::string bytesToHexString(const C& aSequence, bool aUppercase = false)
{
  return bytesToHexString(std::begin(aSequence), std::end(aSequence), aUppercase);
}

int main()
{
  {
    unsigned char buffer[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

    assert(bytesToHexString(buffer, true) == "1122334455");
    assert(bytesToHexString(buffer) == "1122334455");
  }

  {
    std::vector<unsigned char> container{0xBA, 0xAD, 0xF0, 0x0D};
    assert(bytesToHexString(container, true) == "BAADF00D");
    assert(bytesToHexString(container) == "baadf00d");
  }

  {
    std::array<unsigned char, 6> container{1, 2, 3, 4, 5, 6};
    assert(bytesToHexString(container) == "010203040506");
    assert(bytesToHexString(container, true) == "010203040506");
  }
}