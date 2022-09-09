#include <functional>
#include <iostream>

template<typename T>
T minimum(const T a, const T b)
{
  return a < b ? a : b;
}

template<typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
  return minimum(a, minimum(args...));
}

template<class Compare, typename T>
T minimumc(Compare aCompareClass, const T a, const T b)
{
  return aCompareClass(a, b) ? a : b;
}

template<class Compare, typename T1, typename... T>
T1 minimumc(Compare aCompareClass, T1 a, T... args)
{
  return minimumc(aCompareClass, a, minimumc(aCompareClass, args...));
}

int main()
{
  auto x = minimum(5, 4, 2, 3);
  std::cout << x << std::endl;

  auto y = minimumc(std::less<>(), 3, 2, 1, 0);
  std::cout << y << std::endl;
}
