#include <algorithm>
#include <atomic>
#include <cassert>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

const unsigned int NUM_THREADS = std::thread::hardware_concurrency();

void atomicCounter()
{
  std::atomic<int> counter {0};

  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back([&counter]() {
      for (int i = 0; i < 10; ++i) {
        ++counter;
      }
    });
  }

  for (auto& thread: threads) {
    thread.join();
  }

  printf("Atomic counter -> %d", counter.load());
}

void useAtomicFlag()
{
  std::atomic_flag lock = ATOMIC_FLAG_INIT;
  int counter = 0;

  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back([&]() {
      while (lock.test_and_set(std::memory_order_acquire)) {
        ;
      }
      ++counter;
      lock.clear(std::memory_order_release);
    });
  }

  for (auto& thread: threads) {
    thread.join();
  }

  printf("Use atomic flag -> counter -> %d\n", counter);
}

std::vector<int> generateNumbers()
{
  std::random_device rd;
  auto generator = std::mt19937 {rd()};
  auto dis = std::uniform_int_distribution<> {1, 99};
  std::vector<int> numbers(100000, 0);

  std::generate(std::begin(numbers), std::end(numbers), [&dis, &generator] {
    return dis(generator);
  });

  return numbers;
}

void fetchArithmetic()
{
  std::atomic<int> sum {0};
  std::vector<int> numbers = generateNumbers();

  const int sumExpected = std::accumulate(std::begin(numbers), std::end(numbers), 0);

  const size_t size = numbers.size();
  const int step = size / NUM_THREADS;

  std::vector<std::thread> threads;
  for (size_t i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back(
      [&sum, &numbers](const size_t start, const size_t end) {
        for (size_t i = start; i < end; ++i) {
          std::atomic_fetch_add_explicit(&sum, numbers[i], std::memory_order_acquire);
        }
      },
      i * step,
      (i + 1) * step);
  }

  for (auto& thread: threads) {
    thread.join();
  }

  assert(sum == sumExpected);

  printf("FA -> Sum: %d\n", sum.load());
  printf("FA -> Sum expected: %d\n", sumExpected);
}

template<typename T, typename I = typename std::enable_if<std::is_integral<T>::value>::type>
class atomic_counter
{
  std::atomic<T> counter {0};

public:
  T increment()
  {
    return counter.fetch_add(1);
  }

  T decrement()
  {
    return counter.fetch_sub(1);
  }

  T get()
  {
    return counter.load();
  }
};

void counter()
{
  atomic_counter<int> counter;

  std::vector<std::thread> threads;
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.emplace_back([&counter]() {
      for (int i = 0; i < NUM_THREADS; ++i) {
        counter.increment();
      }
    });
  }

  for (auto& thread: threads) {
    thread.join();
  }

  printf("Counter: %d\n", counter.get());
}

int main()
{
  atomicCounter();
  useAtomicFlag();
  fetchArithmetic();
  counter();
}