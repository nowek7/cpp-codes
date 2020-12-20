#pragma once

#include <string>
#include "recipe_3_05.h"
#include "FunctionLib.hpp"

template <typename F, typename G>
auto operator*(F&& f, G&& g)
  {
  return FunctionLib::compose(std::forward<F>(f), std::forward<G>(g));
  }

template <typename F, typename... R>
auto operator*(F&& f, R&&... r)
  {
  return FunctionLib::operator*(std::forward<F>(f), r...);
  }

int main()
  {
  using namespace FunctionLib;

  auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

    {
      auto v = compose(
        [](int const n) { return std::to_string(n); },
        [](int const n) { return n * n; })(-3);

      auto n = compose(
        [](const int n) { return std::to_string(n); },
        [](const int n) { return n * n; },
        [](const int n) { return n + n; },
        [](const int n) { return std::abs(n); })(-3);

      auto s = compose(
        [](std::vector<int> const & v) { return foldl(std::plus<>(), v, 0); },
        [](std::vector<int> const & v) { return mapf([](int const i) {return i + i; }, v); },
        [](std::vector<int> const & v) { return mapf([](int const i) {return std::abs(i); }, v); })(vnums);
    }

    {
      auto n =
        ([](const int n) { return std::to_string(n); } *
         [](const int n) { return n * n; } *
         [](const int n) { return n + n; } *
         [](const int n) { return std::abs(n); })(-3);

      auto c =
        [](const std::vector<int> &v) {
          return foldl(std::plus<>(), v, 0); } *
        [](const std::vector<int> &v) {
          return mapf([](const int i) { return i + i; }, v); } *
        [](const std::vector<int> &v) {
          return mapf([](const int i) { return std::abs(i); }, v); };

      auto s = c(vnums);
    }
  }
