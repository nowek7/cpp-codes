#include <iostream>
#include <string>

template <typename... Ts>
auto add(Ts... args)
  {
  return (... + args);
  }

template <typename... Ts>
auto addr(Ts... args)
  {
  return (args + ...);
  }

template <typename... Ts>
auto allOf(Ts... args)
  {
  return (... && args);
  }

template <typename... Ts>
auto anyOf(Ts... args)
  {
  return (... || args);
  }

template <typename T>
struct wrapper_min
  {
  const T  &value;
  };

template <typename T>
constexpr auto operator<(wrapper_min<T> const & lhs, wrapper_min<T> const & rhs)
  {
  return wrapper_min<T> {lhs.value < rhs.value ? lhs.value : rhs.value};
  }

template <typename... Ts>
constexpr auto min(Ts&&... args)
  {
  return (wrapper_min<Ts>{args} < ...).value;
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
  std::cout << min(10, 2, 3, 4, 5) << std::endl;

  std::cout << add() << std::endl;
  std::cout << add(1, 2, 3, 4, 5) << std::endl;
  std::cout << addr(1, 2, 3, 4, 5) << std::endl;

  std::cout << allOf(true, true, true) << std::endl;
  std::cout << allOf(false, false, false) << std::endl;
  std::cout << allOf(true, false, true) << std::endl;

  std::cout << anyOf(true, true, true) << std::endl;
  std::cout << anyOf(false, false, false) << std::endl;
  std::cout << anyOf(true, false, true) << std::endl;

    {
      auto n = fold(std::plus<>(), 1, 2, 3, 4, 5);
      auto s = fold(std::plus<>(), "hello", " ", "world", "!");
    }


    {
      auto i1 = isAny(42, 1, 23, 76, 44, 5);
      auto a = 0;
    }
  }
