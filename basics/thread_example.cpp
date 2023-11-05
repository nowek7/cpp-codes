#include <algorithm>
#include <array>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

typedef std::uniform_int_distribution<int> uidInt;

std::mutex lockPrint;
std::mutex lockQueue;
std::condition_variable queueCheck;
std::queue<int> buffer;
bool done;

void producer(const int id, std::mt19937& generator, uidInt& dsleep, uidInt& dcode)
{
  for (int i = 0; i < 5; ++i) {
    // Simulate work
    std::this_thread::sleep_for(100ms);

    // Generate data
    int value = id * 100 + dcode(generator);

    {
      std::unique_lock<std::mutex> locker(lockPrint);
      std::cout << "[produced]: " << value << std::endl;
    }

    // Notify consumers
    {
      std::unique_lock<std::mutex> locker(lockQueue);
      buffer.push(value);
      queueCheck.notify_one();
    }
  }
}

void consumer()
{
  // Loop until end is signaled
  while (!done) {
    std::unique_lock<std::mutex> locker(lockQueue);

    queueCheck.wait(locker, [&]() {
      return !buffer.empty();
    });

    // If there are values in the queue process them
    while (!buffer.empty()) {
      std::unique_lock<std::mutex> locker(lockPrint);
      std::cout << "[consumed]: " << buffer.front() << std::endl;
      buffer.pop();
    }
  }
}

int main()
{
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::random_device rd {};

  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  auto generator = std::mt19937 {seq};
  auto dsleep = uidInt {1, 5};
  auto dcode = uidInt {1, 99};

  std::cout << "Start producing and consuming..." << std::endl;
  std::thread consumerthread(consumer);

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.emplace_back(producer, i + 1, std::ref(generator), std::ref(dsleep), std::ref(dcode));
  }

  // Work for the workers to finish
  for (auto& thread: threads) {
    thread.join();
  }

  // Notify the logger to finish and wait for it
  done = true;
  consumerthread.join();

  std::cout << "Done producing and consuming" << std::endl;
}