#include <iostream>
#include <random>
#include <vector>

namespace
{
  constexpr unsigned int COUNT_TEMPERATURES = 100;
  constexpr double MIN = -40;
  constexpr double MAX = 40;
} // namespace

std::vector<double> get_random_temperatures()
{
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_real_distribution<double> urd(MIN, MAX);

  std::vector<double> random_temperatures(COUNT_TEMPERATURES);
  for (auto i = 0; i < COUNT_TEMPERATURES; ++i)
  {
    random_temperatures[i] = urd(engine);
  }

  return random_temperatures;
}

double closest_temperature_to_zero(const std::vector<double>& random_temperatures)
{
  if (random_temperatures.size() == 0)
  {
    return 0.;
  }

  double min = random_temperatures[0];
  for (auto it = random_temperatures.begin() + 1; it != random_temperatures.end(); ++it)
  {
    if (*it > 0. && (*it < min || min <= 0.))
    {
      min = *it;
    }
  }

  return min < 0 ? 0. : min;
}

int main()
{
  const auto random_temperatures = get_random_temperatures();
  const auto min = closest_temperature_to_zero(random_temperatures);
  std::cout << min << std::endl;
}