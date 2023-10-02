#pragma once

#include <algorithm>
#include <vector>

namespace Arithemetic {
  template<typename... T>
  auto sum(T... args)
  {
    return (args + ... + 0);
  }

  template<typename T>
  auto sum(const std::vector<T> numbers)
  {
    return std::acumulate(numbers.begin(), numbers.end(), 0);
  }

  template<typename T>
  T sub(const T lhs, T rhs)
  {
    return lhs - rhs;
  }

  template<typename... Ts>
  auto mul(Ts... args)
  {
    return (... * args);
  }

  template<typename T>
  T div(const T lhs, const T rhs)
  {
    return (rhs != 0) ? (lhs / rhs) : 0;
  }
} //namespace Arithemetic
