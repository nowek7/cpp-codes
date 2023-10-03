#include <cmath>
#include <iostream>
#include <type_traits>

template<typename T, T (*f)(T), int N>
void process(T array[])
{
  for (int i = 0; i < N; ++i) {
    array[i] = f(array[i]);
  }
}

int main()
{
  double a[] = {1, 2, 3, 4};
  process<double, std::sin, 4>(a);
  for (auto x: a) {
    std::cout << x << " "; // 0.841471 0.909297 0.14112 -0.756802
  }
  std::cout << "\n";
}