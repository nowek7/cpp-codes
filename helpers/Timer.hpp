#pragma once

#include <chrono>
#include <cstdio>

namespace TIMER
  {
  class FunctionTimer
    {
    public:
      using ClockType = std::chrono::steady_clock;

      FunctionTimer(const char *func)
        :
        theFunctionName{func},
        theStart{ClockType::now()}
        {}

      FunctionTimer(const FunctionTimer &) = delete;
      FunctionTimer(FunctionTimer &&) = delete;
      auto operator=(const FunctionTimer &)->FunctionTimer & = delete;
      auto operator=(FunctionTimer &&)->FunctionTimer & = delete;

      ~FunctionTimer()
        {
        using namespace std::chrono;

        auto stop = ClockType::now();
        auto ms = duration_cast<std::chrono::milliseconds>(stop - theStart).count();
        printf("%s -> %i ms\n", theFunctionName, static_cast<int>(ms));
        }

    private:
      const char *theFunctionName = {};
      const ClockType::time_point theStart = {};
    };

  template <typename Time = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
  struct perfomanceTimer
    {
    template <typename F, typename... Args>
    static Time duration(F &&f, Args... args)
      {
      auto start = Clock::now();
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
      }
    };
  };
