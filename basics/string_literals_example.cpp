#include <array>
#include <iostream>

namespace ComputerUnits {
  constexpr size_t operator"" _KB(const unsigned long long aSize)
  {
    return static_cast<size_t>(aSize * 1024);
  }
} // namespace ComputerUnits

int main()
{
  using namespace ComputerUnits;

  auto memory = 4_KB;
  std::cout << memory << std::endl;

  auto size = 8_KB;
  std::cout << size << std::endl;

  auto buffer = std::array<std::byte, 1_KB> {};
}