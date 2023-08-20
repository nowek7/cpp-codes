#include <chrono>
#include <iostream>

constexpr auto LIMIT = 1'000'000;

bool isOddModulo(int aNumber)
{
  return aNumber % 2;
}

bool isOddBitwiseOperator(int aNumber)
{
  return aNumber & 1;
}

void benchmark()
{
  bool parity = false;

  auto start = std::chrono::steady_clock::now();
  for (auto i = 0; i < LIMIT; i++)
  {
    parity = isOddModulo(i);
  }
  auto end = std::chrono::steady_clock::now();

  std::cout << "MODULO OPERATOR: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms" << std::endl;

  start = std::chrono::steady_clock::now();
  for (auto i = 0; i < LIMIT; i++)
  {
    parity = isOddBitwiseOperator(i);
  }
  end = std::chrono::steady_clock::now();

  std::cout << "BITWISE & OPERATOR: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms" << std::endl;
}

int main()
{
  benchmark();
}