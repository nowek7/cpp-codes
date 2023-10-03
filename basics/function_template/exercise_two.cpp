#include <cstring>
#include <iostream>
#include <type_traits>

template<typename T>
int compare(T a, T b)
{
  if (std::is_arithmetic<T>::value || std::is_pointer<T>::value || std::is_reference<T>::value) {
    return a < b ? 1 : (b < a ? -1 : 0);
  }
}

template<>
int compare(std::string a, std::string b)
{
  return strcmp(a.c_str(), b.c_str());
}

int main()
{
  int a = 1;
  int b = -6;
  float y = 1.0 + 1e20 - 1e20;
  float x = 1.0;

  std::cout << compare(a, b) << " " << compare(b, a) << " " << compare(a, a) << std::endl;
  std::cout << compare(x, y) << " " << compare(y, x) << " " << compare(x, x) << std::endl;
  std::cout << compare(&a, &b) << " " << compare(&b, &a) << " " << compare(&a, &a) << std::endl;
  std::cout << compare(&x, &y) << " " << compare(&y, &x) << " " << compare(&x, &x) << std::endl;
  std::cout << compare("Alpha", "Alfa") << std::endl;
}