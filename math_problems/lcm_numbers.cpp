#include <iostream>
#include <numeric>
#include <vector>

constexpr unsigned int LIMIT = 10;

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b)
{
  int res = gcd(a, b);
  return res ? (a * (b / res)) : 0;
}

template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
  return std::accumulate(first, last, 1, lcm);
}

int main()
{
  std::vector<int> numbers;
  for (int i = 0; i < LIMIT; ++i) {
    numbers.push_back(i + 10);
  }

  auto lcm = [](const std::vector<int>& aContainer) {
    return lcmr(aContainer.begin(), aContainer.end());
  };

  std::cout << "LCM of container numbers -> " << lcm(numbers) << std::endl;
}