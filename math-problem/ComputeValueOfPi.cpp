#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <random>

template <typename E = std::mt19937, typename D = std::uniform_real_distribution<>>
double computePi(E &engine, D &dist, int const samples = 1000000)
  {
  auto hit = 0;
  for (auto i = 0; i < samples; i++)
    {
    auto x = dist(engine);
    auto y = dist(engine);

    if (y <= std::sqrt(1 - std::pow(x, 2)))
      hit += 1;
    }

  return 4.0 * hit / samples;
  }

int main()
  {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));

  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  auto engine = std::mt19937{ seq };
  auto distribution = std::uniform_real_distribution<>{0, 1};

  for (auto i = 0; i < 100; i++)
    std::cout << computePi(engine, distribution) << std::endl;
  }