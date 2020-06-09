#include <chrono>
#include <random>
#include <iostream>

constexpr int CONTAINER_SIZE = 10'000;
constexpr int MIN_CONTAINER_SIZE = 10;

int **getRandomNumberContainer()
  {
  std::random_device device;
  std::mt19937_64 engine(device());
  std::uniform_int_distribution<int> distrubution(-100, 100);

  int **numbersContainer = new int *[CONTAINER_SIZE];
  for (int i = 0; i < CONTAINER_SIZE; i++)
    numbersContainer[i] = new int(distrubution(engine));

  return numbersContainer;
  }

void showNumberContainer(int **aNumbersContainer, int aSize = CONTAINER_SIZE)
  {
  std::cout << "===========================" << std::endl;

  for (int i = 0; i < aSize - 1; i++)
    std::cout << *aNumbersContainer[i] << ", ";
  std::cout << *aNumbersContainer[aSize - 1] << std::endl;

  std::cout << "===========================" << std::endl;
  }

void removeNumbers(int **aNumbersContainer, int aSize = CONTAINER_SIZE)
  {
  // Free memory.
  for (int i = 0; i < aSize; i++)
    delete aNumbersContainer[i];
  delete aNumbersContainer;
  }

void insertionSort(int **aNumbersContainer, bool aAsceding = true)
  {
  for (int i = 1; i < CONTAINER_SIZE; ++i)
    {
    auto j = i;

    bool condition = aAsceding ? (*aNumbersContainer[j - 1] > * aNumbersContainer[j]) : (*aNumbersContainer[j - 1] < *aNumbersContainer[j]);
    while (j > 0 && condition)
      {
      auto temp = *aNumbersContainer[j - 1];
      *aNumbersContainer[j - 1] = *aNumbersContainer[j];
      *aNumbersContainer[j] = temp;

      --j;
      }
    }
  }

int main()
  {
  int **numbersContainer = getRandomNumberContainer();

  std::cout << "Sorting " << CONTAINER_SIZE << " random numbers." << std::endl;
  std::cout << "======================================" << std::endl;

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== Before sorting ========" << std::endl;
      showNumberContainer(numbersContainer);
      }
  #endif // _DEBUG

  auto start = std::chrono::steady_clock::now();
  insertionSort(numbersContainer);
  auto end = std::chrono::steady_clock::now();

  std::cout << "Time of insertion sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << std::endl;

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== After sorting ========" << std::endl;
      showNumberContainer(numbersContainer);
      }
  #endif // _DEBUG

  removeNumbers(numbersContainer);

  return 0;
  }