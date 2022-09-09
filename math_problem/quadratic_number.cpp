// Algorytm sprawdzający czy dana liczba jest bezkwadratowa

#include <algorithm>
#include <functional>
#include <random>
#include <set>

namespace
{
  constexpr int MIN = 1;
  constexpr int MAX = 1000;

  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<> uid(MIN, MAX);
} // namespace

std::vector<int> getRandomSequence(int aSize)
{
  std::vector<int> numbers;
  while (numbers.size() <= aSize)
  {
    const int number = uid(engine);
    if (std::find(numbers.cbegin(), numbers.cend(), number) == numbers.cend())
    {
      numbers.push_back(number);
    }
  }

  return numbers;
}

void printNumbers(const std::vector<int>& aNumbers)
{
  for (auto i = 0; i < aNumbers.size(); ++i)
  {
    printf("%4d", aNumbers[i]);
  }
  printf("\n");
}

std::pair<int, int> getMinMax(const std::vector<int>& aNumbers)
{
  const auto& [min, max] = std::minmax_element(aNumbers.begin(), aNumbers.end(), std::less<int>());
  return std::make_pair(*min, *max);
}

std::vector<int> getSquares(const int& aLimit)
{
  std::vector<int> squares(aLimit);
  for (int i = 0; i <= aLimit; i++)
  {
    squares.emplace_back(i * i);
  }

  return squares;
}

std::vector<std::pair<int, int>> getQuadraticPairs(const std::vector<int>& aNumbers)
{
  const auto& [min, max] = getMinMax(aNumbers);
  const auto& squares = getSquares(max);

  std::vector<std::pair<int, int>> pairs;
  for (auto i = 0; i < aNumbers.size(); i++)
  {
    for (auto j = i + 1; j < aNumbers.size(); j++)
    {
      const int result = aNumbers[i] * aNumbers[j];
      const bool found = std::binary_search(squares.cbegin(), squares.cend(), result);
      if (found)
      {
        pairs.emplace_back(aNumbers[i], aNumbers[j]);
      }
    }
  }

  return pairs;
}

void printQuadraticPairs(const std::vector<std::pair<int, int>>& aPairs)
{
  for (auto it = aPairs.cbegin(); it != aPairs.cend(); ++it)
  {
    const auto& [left, right] = *it;
    printf("{%d, %d} -> %d\n", left, right, left * right);
  }
}

int main()
{
  const int size = 100;

  std::vector<int> numbers;
  std::vector<std::pair<int, int>> pairs;
  do
  {
    numbers = getRandomSequence(size);
    pairs = getQuadraticPairs(numbers);
  }
  while (pairs.empty());

  printQuadraticPairs(pairs);
}