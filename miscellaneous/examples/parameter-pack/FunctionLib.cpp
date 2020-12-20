#include "FunctionLib.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std::string_literals;

template<class T = double>
struct fround
  {
  typename std::enable_if<std::is_floating_point<T>::value, T>::type
  operator()(const T& value) const
    {
    return std::round(value);
    }
  };

int main()
  {
    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto r = FunctionLib::mapf([](int const i) {return std::abs(i); }, vnums);
      // r = {0, 2, 3, 5, 1, 6, 8, 4, 9}

      auto lnums = std::list<int>{ 1, 2, 3, 4, 5 };
      auto l = FunctionLib::mapf([](int const i) {return i*i; }, lnums);
      // l = {1, 4, 9, 16, 25}

      auto amounts = std::array<double, 5> {10.42, 2.50, 100.0, 23.75, 12.99};
      auto a = FunctionLib::mapf(fround<>(), amounts);
      // a = {10.0, 3.0, 100.0, 24.0, 13.0}

      auto words = std::map<std::string, int>{ { "one", 1 },{ "two", 2 },{ "three", 3 } };
      auto m = FunctionLib::mapf([](std::pair<std::string, int> const kvp)
        {
        return std::make_pair(FunctionLib::mapf(toupper, kvp.first), kvp.second);
        }, words);
      // m = { {"ONE", 1}, {"TWO", 2}, {"THREE", 3} }

      auto priorities = std::queue<int>();
      priorities.push(10);
      priorities.push(20);
      priorities.push(30);
      priorities.push(40);
      priorities.push(50);
      auto p = FunctionLib::mapf([](int const i) {return i > 30 ? 2 : 1; }, priorities);
      // p = {1, 1, 1, 2, 2}
    }

    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto s1 = FunctionLib::foldl([](const int s, const int n) {return s + n; }, vnums, 0); // s1 = 22
      auto s2 = FunctionLib::foldl(std::plus<>(), vnums, 0); // s2 = 22

      auto s3 = FunctionLib::foldr([](const int s, const int n) {return s + n; }, vnums, 0); // s3 = 22
      auto s4 = FunctionLib::foldr(std::plus<>(), vnums, 0); // s4 = 22

      auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };
      auto txt1 = FunctionLib::foldl([](std::string const & s, std::string const & n) {return s + n; }, texts, ""s);
      // txt1 = "hello world!"
      auto txt2 = FunctionLib::foldr([](std::string const & s, std::string const & n) {return s + n; }, texts, ""s);
      // txt2 = "!world hello"

      char chars[] = { 'c','i','v','i','c' };
      auto str1 = FunctionLib::foldl(std::plus<>(), chars, ""s); // str1 = "civic"
      auto str2 = FunctionLib::foldr(std::plus<>(), chars, ""s); // str2 = "civic"

      auto words = std::map<std::string, int>{ { "one", 1 },{ "two", 2 },{ "three", 3 } };
      auto count = FunctionLib::foldl(
        [](int const s, std::pair<std::string, int> const kvp) {return s + kvp.second; },
        words,
        0);

      auto q = std::queue<int>{};
      q.push(1);
      q.push(2);
      q.push(3);
      q.push(4);
      q.push(5);
      auto sum = FunctionLib::foldl(std::plus<>(), q, 0); // sum = 15
    }

    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

      auto s = FunctionLib::foldl(
        std::plus<>(),
        FunctionLib::mapf(
          [](int const i) { return i + i; },
          FunctionLib::mapf(
            [](int const i) { return std::abs(i); },
            vnums)),
          0);
      // s = 76
    }
  }
