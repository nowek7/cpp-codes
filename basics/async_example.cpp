#include <algorithm>
#include <random>
#include <future>

class Car
  {
  const double MIN_AMOUNT_FUEL = 5.0;

  public:
    void run()
      {
      auto future = std::async(std::launch::async, &Car::getAmountOfFuel, this);
      const double amountFuel = future.get();

      if (amountFuel < MIN_AMOUNT_FUEL)
        printf("Can't run the car. Not enough fuel only %-1.3fl.\n", amountFuel);
      else
        printf("Can run car.\n");
      }

    double getAmountOfFuel()
      {
      std::random_device rd{};
      std::mt19937_64 engine(rd());
      std::uniform_real_distribution<double> urd(0, 10);

      return urd(engine);
      }
  };

bool isPrime(const int aNumber)
  {
  if (((!(aNumber & 1)) && aNumber != 2) ||
                          (aNumber < 2) ||
                          (aNumber % 3 == 0 && aNumber != 3))
    return (false);

  for (int k = 1; 36 * k * k - 12 * k < aNumber; ++k)
    {
    if ((aNumber % (6 * k + 1) == 0) ||
        (aNumber % (6 * k - 1) == 0))
      return (false);
    }

  return true;
  }

std::vector<int> getPrimesNumbers(std::vector<int>::iterator aBegin, std::vector<int>::iterator aEnd)
  {
  std::vector<int> primes;
  for (auto it = aBegin; it != aEnd; ++it)
    {
    if (isPrime(*it))
      primes.push_back(*it);
    }

  return primes;
  }


int main()
  {
    {
    printf("===Section 1===\n");
    Car vehicle;
    vehicle.run();
    }

    {
    printf("===Section 2===\n");
    Car vehicle;
    auto future = std::async(std::launch::async, &Car::getAmountOfFuel, &vehicle);
    printf("Car has %-1.3fl\n", future.get());
    }

    {
    printf("===Section 3===\n");

    std::random_device rd{};
    std::mt19937_64 engine(rd());
    std::uniform_int_distribution uid(0, 100);

    const int COUNT = 100;
    std::vector<int> numbers(COUNT);
    std::generate(numbers.begin(), numbers.end(), [&uid, &engine]() { return uid(engine); });

    auto primes1 = getPrimesNumbers(numbers.begin(), numbers.begin() + (COUNT * 0.5));
    auto primes2 = std::async(std::launch::async, &getPrimesNumbers, numbers.begin() + (COUNT * 0.5), numbers.end());

    for (auto &&primes : primes1)
      printf("Primes1: %5d\n", primes);

    primes2.wait();
    for (auto &&primes : primes2.get())
      printf("Primes2: %5d\n", primes);
    }
  }