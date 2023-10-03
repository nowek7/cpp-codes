#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

template<typename T>
constexpr T sqr(T x)
{
  if constexpr (std::is_arithmetic_v<T> && !std::is_same_v<T, char>) {
    return x * x;
  } else {
    return T {};
  }
}

template<>
std::string sqr<std::string>(std::string x)
{
  return x + x;
}

template<int N>
constexpr int mod(int x)
{
  return N != 0 ? x % N : -x;
}

template<class Container>
void print(const Container& v)
{
  for (const auto& entry: v) {
    std::cout << entry << " ";
  }
  std::cout << "\n";
}

template<typename C, typename F>
C custom_apply(const C& c, F f)
{
  C container;
  std::transform(std::begin(c), std::end(c), std::back_inserter(container), [&f](auto&& entry) {
    return f(entry);
  });
  return container;
}

int main()
{
  std::cout << sqr(4) << std::endl;                  // 16
  std::cout << sqr(14.5) << std::endl;               // 210.25
  std::cout << sqr(std::string("hey")) << std::endl; // heyhey

  std::cout << "***************************" << std::endl;

  std::cout << mod<5>(131) << std::endl; // 1
  std::cout << mod<7>(131) << std::endl; // 5
  std::cout << mod<0>(131) << std::endl; // -131

  std::cout << "***************************" << std::endl;

  std::vector<int> v = {1, 21, 34, 4, 15};
  print(v); // 1 21 34 4 15

  std::list<double> l = {1, 2.1, 3.2, 6.3};
  print(l); // 1 2.1 3.2 6.3

  std::cout << "***************************" << std::endl;

  auto w = custom_apply(v, sqr<int>);
  auto w2 = custom_apply(w, mod<5>);
  print(w2); // 1 1 1 1 0

  auto l2 = custom_apply(l, sqr<double>);
  auto l3 = custom_apply(l2, mod<5>);
  print(l3); // 1 4 0 4

  // Function sin is overloaded; cast it to avoid ambiguity
  auto l4 = custom_apply(l3, static_cast<double (*)(double)>(std::sin));
  print(l4); // 0.841471 -0.756802 0 -0.756802
}
