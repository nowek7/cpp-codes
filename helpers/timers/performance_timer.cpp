#pragma once

#include <chrono>
#include <cstdio>

template<typename Time = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
struct PerformanceTimer
{
  template<typename F, typename... Args>
  static Time duration(F&& f, Args... args)
  {
    auto start = Clock::now();
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = Clock::now();

    return std::chrono::duration_cast<Time>(end - start);
  }
};
