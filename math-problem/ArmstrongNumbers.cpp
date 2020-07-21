#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>

int main()
  {
  auto printAllArmstrongNumbersWithThreeDigits = [](bool aToPrint = false)
    {
    auto start = std::chrono::steady_clock::now();
    for (auto i = 100; i < 1000; i++)
      {
      auto armstrongNum = int{0};
      auto num = i;
      while (num != 0)
        {
        armstrongNum += std::pow(num % 10, 3);
        num /= 10;
        }

      if (armstrongNum == i && aToPrint)
        std::cout << i << std::endl;
      }

    auto end = std::chrono::steady_clock::now();

    std::cout << "---------------------" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    };

  auto printAllArmstrongNumbersWithThreeDigits2 = [](bool aToPrint = false)
    {
    auto start = std::chrono::steady_clock::now();
    for (int i = 100; i < 1000; i++)
      {
      std::vector<int> digits;
      int n = i;
      while (n > 0)
        {
        digits.push_back(n % 10);
        n /= 10;
        }

      int arm = std::accumulate(
         std::begin(digits), std::end(digits),
         0,
         [s = digits.size()](int const sum, int const digit) {return sum + static_cast<int>(std::pow(digit, s)); });

      if (i == arm)
        {
         if (aToPrint)
          std::cout << arm << std::endl;
        }
      }

    auto end = std::chrono::steady_clock::now();

    std::cout << "---------------------" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    };

  // I think, it is not an elegant form.
  auto printAllArmstrongNumbersWithThreeDigits3 = [](bool aToPrint = false)
    {
    auto start = std::chrono::steady_clock::now();
    for (auto i = 1; i < 10; i++)
      {
      auto firstPart = std::pow(i, 3);
      for (auto j = 0; j < 10; j++)
        {
        auto secondPart = std::pow(j, 3);
        for (auto k = 0; k < 10; k++)
          {
          auto number = firstPart + secondPart + std::pow(k, 3);
          if (number == ((i * 100) + (j * 10) + k) && aToPrint)
            std::cout << number << std::endl;
          }
        }
      }

    auto end = std::chrono::steady_clock::now();
    std::cout << "---------------------" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    };

  printAllArmstrongNumbersWithThreeDigits(true);
  std::cout << "---------------------" << std::endl;
  printAllArmstrongNumbersWithThreeDigits2(true);
  std::cout << "---------------------" << std::endl;
  printAllArmstrongNumbersWithThreeDigits3(true);
  std::cout << "---------------------" << std::endl;
  }