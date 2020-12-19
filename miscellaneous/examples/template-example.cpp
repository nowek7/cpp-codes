#include <string>
#include <assert.h>

template <typename T>
T sum(T value)
  {
  return value;
  }

template <typename T, typename... Ts>
T sum(T head, Ts... tail)
  {
  return head + sum(tail...);
  }

template <typename F, typename T1, typename T2>
auto fold(F&& f, T1 v1, T2 v2)
  {
  return f(v1, v2);
  }

template <typename F, typename T, typename... Ts>
auto fold(F&& f, T head, Ts... tail)
  {
  return f(head, fold(std::forward<F>(f), tail...));
  }

template <typename T>
bool isFibonacci(T v1, T v2, T v3)
  {
  return v1 + v2 == v3;
  }

/*
  template <typename T, typename... Ts>
  bool isFibonacci(T v1, T v2, T v3, Ts... args)
    {
    return v1 + v2 == v3 && isFibonacci(args...);
    }
*/

template <typename T>
bool isAny(T value, T elem)
  {
  return value == elem;
  }

template <typename T, typename... Ts>
bool isAny(T value, T first, Ts... rest)
  {
  return value == first || isAny(value, rest...);
  }

int main()
  {
  using namespace std::string_literals;

    {
      auto n = sum(1, 2, 3, 4, 5);
      auto s = sum("hello"s, " "s, "world"s, "!"s);

      assert(15 == n);

      std::string check = "hello world!";
      assert(check == s);
    }

    {
      auto n = fold(std::plus<>(), 1, 2, 3, 4, 5);
      auto s = fold(std::plus<>(), "hello"s, " "s, "world"s, "!"s);

      assert(15 == n);

      std::string check = "hello world!";
      assert(check == s);
    }

    {
      auto i1 = isAny(42, 1, 23, 76, 44, 5);
      auto a = 0;
    }
  }