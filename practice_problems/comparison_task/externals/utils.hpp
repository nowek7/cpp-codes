#pragma once

#include <chrono>
#include <functional>

template<typename Time = std::chrono::milliseconds, typename Clock = std::chrono::high_resolution_clock>
struct performanceTimer
{
  template<typename F, typename... Args>
  static Time duration(F&& f, Args... args)
  {
    auto start = Clock::now();
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    auto end = Clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  }
};
