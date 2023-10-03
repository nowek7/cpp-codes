#include <iostream>
#include <random>

namespace {
  constexpr int COUNT = 10;
  constexpr int MIN = 1;
  constexpr int MAX = 100;
} // namespace

void print(int* aNumbers)
{
  for (int i = 0; i < COUNT - 1; i++) {
    printf("%d, ", aNumbers[i]);
  }
  printf("%d \n", aNumbers[COUNT - 1]);
}

void generateNumbers(int* aNumbers)
{
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<> uid(MIN, MAX);

  for (int i = 0; i < COUNT; i++) {
    aNumbers[i] = uid(engine);
  }
}

int gcd(const int a, const int b)
{
  if (a == 0) {
    return b;
  }

  return gcd(b % a, a);
}

int lcd(int* aNumbers)
{
  if (!aNumbers[0]) {
    throw std::logic_error("No numbers!");
  }

  if (!aNumbers[1]) {
    return aNumbers[0];
  }

  int value = gcd(aNumbers[0], aNumbers[1]);
  for (int i = 2; i < COUNT; i++) {
    value = gcd(value, aNumbers[i]);
  }

  return value;
}

int main()
{
  int* numbers = new int[COUNT];
  generateNumbers(numbers);
  print(numbers);
  const int value = lcd(numbers);
  printf("LCD in above numbers is -> %d\n", value);

  delete[] numbers;
}