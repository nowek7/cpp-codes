#pragma once

#include <chrono>
#include <cstdio>

class FunctionTimer
{
public:
  using ClockType = std::chrono::steady_clock;

  FunctionTimer(const char* func):
    theFunctionName(func),
    theStart(ClockType::now())
  {
  }

  FunctionTimer(const FunctionTimer&) = delete;
  FunctionTimer(FunctionTimer&&) = delete;

  FunctionTimer& operator=(const FunctionTimer&) = delete;
  FunctionTimer& operator=(FunctionTimer&&) = delete;

  ~FunctionTimer()
  {
    using namespace std::chrono;

    auto stop = ClockType::now();
    auto ms = duration_cast<std::chrono::milliseconds>(stop - theStart).count();
    printf("%s -> %i ms\n", theFunctionName, static_cast<int>(ms));
  }

private:
  const char* theFunctionName;
  const ClockType::time_point theStart;
};