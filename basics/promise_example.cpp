#include <future>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

std::mutex g_mutex;

void produceValue(std::promise<int>& aPromise)
{
  // simulate long running operation
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
  }

  std::random_device rd;
  std::mt19937_64 engine(rd());
  std::uniform_int_distribution<int> uid(0, 100);

  auto value = uid(engine);
  aPromise.set_value(value);
}

void consumeValue(std::future<int>& aFuture)
{
  auto value = aFuture.get();

  std::lock_guard<std::mutex> lock(g_mutex);
  std::cout << value << std::endl;
}

int main()
{
  std::promise<int> p;
  std::thread t1(produceValue, std::ref(p));

  std::future<int> f = p.get_future();
  std::thread t2(consumeValue, std::ref(f));

  t1.join();
  t2.join();
}