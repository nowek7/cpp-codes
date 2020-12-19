#include <iostream>

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
  }
