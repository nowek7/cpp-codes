#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>

constexpr int SIZE = 1'000'000;
constexpr int ITERATION = 100;

auto getLambda()
{
  return [](int aValue)
  {
    return aValue * 3;
  };
}

auto testLambda()
{
  auto lbd = getLambda();
  auto lambdas = std::vector<decltype(lbd)>{};
  lambdas.resize(SIZE, lbd);

  auto start = std::chrono::steady_clock::now();

  auto res = int{0};
  for (const auto& func: lambdas)
  {
    res = func(res);
  }

  auto end = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

auto testStdFunction()
{
  auto lbd = getLambda();
  auto functions = std::vector<std::function<int(int)>>{};
  functions.resize(SIZE, lbd);

  auto start = std::chrono::steady_clock::now();

  auto res = int{0};
  for (const auto& func: functions)
  {
    res = func(res);
  }

  auto end = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main()
{
  auto sumLambdaTimes = double{0};
  auto sumStdFunctionTimes = double{0};
  for (int i = 0; i < ITERATION; i++)
  {
    sumLambdaTimes += testLambda();
    sumStdFunctionTimes += testStdFunction();
  }

  auto meanLambdaTime = sumLambdaTimes / ITERATION;
  auto meanStdFunctionTime = sumStdFunctionTimes / ITERATION;

  std::cout << "Mean time of execute lambda -> " << meanLambdaTime << " microseconds" << std::endl;
  std::cout << "Mean time of execute std::function -> " << meanStdFunctionTime << " microseconds" << std::endl;
}