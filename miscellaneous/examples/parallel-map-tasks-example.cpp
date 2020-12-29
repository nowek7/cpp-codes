#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <numeric>

#include <cassert>

template <typename Time = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
struct perf_timer
  {
  template <typename F, typename... Args>
  static Time duration(F&& f, Args... args)
    {
    auto start = Clock::now();

    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

    auto end = Clock::now();
    return std::chrono::duration_cast<Time>(end - start);
    }
  };

unsigned getNumThreads()
  {
  return std::thread::hardware_concurrency();
  }

namespace versionOne
  {
  template <typename Iter, typename F>
  void parallelMap(Iter begin, Iter end, F f)
    {
    const auto size = std::distance(begin, end);
    if (size <= 10000)
      std::transform(begin, end, begin, std::forward<F>(f));
    else
      {
      auto numTasks = getNumThreads();
      auto part = size / numTasks;
      auto last = begin;

      std::vector<std::future<void>> tasks;
      for (unsigned i = 0; i < numTasks; ++i)
        {
        if (i == numTasks - 1)
          last = end;
        else
          std::advance(last, part);

        tasks.emplace_back(
          std::async(std::launch::async,
          [=, &f]
            {
            std::transform(begin, last, begin, std::forward<F>(f));
            }));

        begin = last;
        }

      for (auto &task : tasks)
        task.wait();
      }
    }

  template <typename Iter, typename R, typename F>
  auto parallelReduce(Iter begin, Iter end, R init, F op)
    {
    const auto size = std::distance(begin, end);
    if (size <= 10000)
      return std::accumulate(begin, end, init, std::forward<F>(op));
    else
      {
      auto numTasks = getNumThreads();
      auto part = size / numTasks;
      auto last = begin;

      std::vector<std::future<R>> tasks;
      for (unsigned i = 0; i < numTasks; ++i)
        {
        if (i == numTasks - 1)
          last = end;
        else
          std::advance(last, part);

        tasks.emplace_back(std::async(std::launch::async, [=, &op] { return std::accumulate(begin, last, R{}, std::forward<F>(op)); }));
        begin = last;
        }

      std::vector<R> values;
      for (auto &task : tasks)
        values.push_back(task.get());

      return std::accumulate(std::begin(values), std::end(values), init, std::forward<F>(op));
      }
    }
  }

namespace versionSecond
  {
  template <typename Iter, typename F>
  void parallelMap(Iter begin, Iter end, F f)
    {
    const auto size = std::distance(begin, end);
    if (size <= 10000)
      std::transform(begin, end, begin, std::forward<F>(f));
    else
      {
      auto middle = begin;
      std::advance(middle, size * 0.5);

      auto result = std::async(std::launch::deferred, parallelMap<Iter, F>, begin, middle, std::forward<F>(f));
      parallelMap(middle, end, std::forward<F>(f));
      result.wait();
      }
    }

  template <typename Iter, typename R, typename F>
  auto parallelReduce(Iter begin, Iter end, R init, F op)
    {
    const auto size = std::distance(begin, end);
    if (size <= 10000)
      return std::accumulate(begin, end, init, std::forward<F>(op));
    else
      {
      auto middle = begin;
      std::advance(middle, size * 0.5);

      auto result1 = std::async(
        std::launch::async,
        parallelReduce<Iter, R, F>,
        begin, middle, R{},
        std::forward<F>(op));

      auto result2 = parallelReduce(middle, end, init, std::forward<F>(op));
      return result1.get() + result2;
      }
    }
  }

void testMapReduceTasks()
  {
  std::vector<int> sizes
    {
      10000, 100000, 500000,
      1000000, 2000000, 5000000,
      10000000
    };

  std::cout
    << std::right << std::setw(8) << std::setfill(' ') << "size"
    << std::right << std::setw(8) << "s map"
    << std::right << std::setw(8) << "p1 map"
    << std::right << std::setw(8) << "p2 map"
    << std::right << std::setw(8) << "s fold"
    << std::right << std::setw(8) << "p1 fold"
    << std::right << std::setw(8) << "p2 fold"
  << std::endl;

  for(const auto size : sizes)
    {
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), 1);

    auto v1 = v;
    auto s1 = 0LL;

    auto tsm = perf_timer<>::duration(
      [&]
        {
        std::transform(std::begin(v1), std::end(v1), std::begin(v1), [](int const i) {return i + i; });
        });

    auto tsf = perf_timer<>::duration([&] {
    s1 = std::accumulate(std::begin(v1), std::end(v1), 0LL, std::plus<>()); });

    auto v2 = v;
    auto s2 = 0LL;
    auto tp1m = perf_timer<>::duration(
      [&]
        {
        versionOne::parallelMap(std::begin(v2), std::end(v2), [](int const i) { return i + i; });
        });

    auto tp1f = perf_timer<>::duration(
      [&]
        {
        s2 = versionOne::parallelReduce(std::begin(v2), std::end(v2), 0LL, std::plus<>());
        });

    auto v3 = v;
    auto s3 = 0LL;
    auto tp2m = perf_timer<>::duration(
      [&]
        {
        versionSecond::parallelMap(std::begin(v3), std::end(v3), [](int const i) { return i + i; });
        });

    auto tp2f = perf_timer<>::duration(
      [&]
        {
        s3 = versionSecond::parallelReduce(std::begin(v3), std::end(v3), 0LL, std::plus<>());
        });

    assert(v1 == v2);
    assert(v1 == v3);

    assert(s1 == s2);
    assert(s1 == s3);

    std::cout
      << std::right << std::setw(8) << std::setfill(' ') << size
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tsm).count()
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tp1m).count()
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tp2m).count()
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tsf).count()
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tp1f).count()
      << std::right << std::setw(8) << std::chrono::duration<double, std::micro>(tp2f).count()
    << std::endl;
    }
  }

int main()
  {
  testMapReduceTasks();
  }
