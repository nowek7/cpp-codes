#include <iostream>
#include <list>
#include <memory> // for std::allocator<>
#include <vector>

template<template<typename T, typename Alloc = std::allocator<T>> typename OutContainer,
         template<typename T, typename Alloc = std::allocator<T>> typename InContainer = std::vector>
OutContainer<int> selectIf(InContainer<int> in, bool (*predicate)(int))
{
  OutContainer<int> out;
  for (auto it = std::begin(in); it != std::end(in); ++it) {
    if (predicate(*it)) {
      out.insert(out.end(), std::forward<int>(*it));
    }
  }

  return out;
}

bool biggerThan5(int x)
{
  return x > 5;
}

int main()
{
  std::vector<int> v = {1, 2, 13, 4, 5, 54};
  std::list<int> result = selectIf<std::list>(v, biggerThan5);

  for (auto entry: result) {
    std::cout << entry << " ";
  }
  std::cout << "\n";
}