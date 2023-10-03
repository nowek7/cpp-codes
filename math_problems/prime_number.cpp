#include <chrono>
#include <iostream>

bool isPrime(const int aNumber)
{
  if (aNumber < 2) {
    return false;
  }

  if (aNumber <= 3) {
    return true;
  }

  for (int i = 2; i * i <= aNumber; i++) {
    if (aNumber % i == 0) {
      return false;
    }
  }

  return true;
};

bool isPrime2(const int aNumber)
{
  if (((aNumber & 1 == 0) && aNumber != 2) || (aNumber < 2) || (aNumber % 3 == 0 && aNumber != 3)) {
    return false;
  }

  for (int k = 1; 36 * k * k - 12 * k < aNumber; ++k) {
    if ((aNumber % (6 * k + 1) == 0) || (aNumber % (6 * k - 1) == 0)) {
      return false;
    }
  }

  return true;
}

int main()
{
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < 100'000; i++) {
      if (isPrime(i)) {
        continue;
      }
      // std::cout << i << " is prime number." << std::endl;
    }

    auto time =
      std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "isPrime -> " << time << "[ms]" << std::endl;
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < 100'000; i++) {
      if (isPrime2(i)) {
        continue;
      }
      // std::cout << i << " is prime number." << std::endl;
    }

    auto time =
      std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "isPrime2 -> " << time << "[ms]" << std::endl;
  }
}
