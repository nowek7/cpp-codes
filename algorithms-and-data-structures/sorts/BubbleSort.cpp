#include <chrono>
#include <iostream>
#include <random>

constexpr int CONTAINER_SIZE = 10'000;
constexpr int MIN_CONTAINER_SIZE = 10;

int **getRandomNumbersContainer()
  {
  std::random_device device;
  std::mt19937_64 engine(device());
  std::uniform_int_distribution<int> distrubution(-100, 100);

  int **numbersContainer = new int *[CONTAINER_SIZE];
  for (int i = 0; i < CONTAINER_SIZE; i++)
    numbersContainer[i] = new int(distrubution(engine));

  return numbersContainer;
  }

void showNumbersContainer(int **aNumbersContainer, int aSize = CONTAINER_SIZE)
  {
  std::cout << "===========================" << std::endl;

  for (int i = 0; i < aSize - 1; i++)
    std::cout << *aNumbersContainer[i] << ", ";
  std::cout << *aNumbersContainer[aSize - 1] << std::endl;

  std::cout << "===========================" << std::endl;
  }

void bubbleSort(int **aNumbersContainer, bool aAsceding = true)
  {
  for (int i = 0; i < CONTAINER_SIZE; i++)
    {
    for (int j = 0; j < CONTAINER_SIZE - 1; j++)
      {
      bool condition = aAsceding ? (*aNumbersContainer[j] > * aNumbersContainer[j + 1]) : (*aNumbersContainer[j] < *aNumbersContainer[j + 1]);
      if (condition)
        {
        int temp = *aNumbersContainer[i];
        *aNumbersContainer[i] = *aNumbersContainer[j];
        *aNumbersContainer[j] = temp;
        }
      }
    }
  }

void bubbleSortUsingFlag(int **aNumbersContainer, bool aAsceding = true)
  {
  bool sorted = false;
  for (int i = 0; (i < CONTAINER_SIZE) && !sorted; i++)
    {
    sorted = true;
    for (int j = 0; j < CONTAINER_SIZE - 1; j++)
      {
      bool condition = aAsceding ? (*aNumbersContainer[j] > * aNumbersContainer[j + 1]) : (*aNumbersContainer[j] < *aNumbersContainer[j + 1]);
      if (condition)
        {
        sorted = false;
        int temp = *aNumbersContainer[j];
        *aNumbersContainer[j] = *aNumbersContainer[j + 1];
        *aNumbersContainer[j + 1] = temp;
        }
      }
    }
  }

void removeNumbers(int **aNumbersContainer, int aSize = CONTAINER_SIZE)
  {
  // Free memory.
  for (int i = 0; i < aSize; i++)
    delete aNumbersContainer[i];
  delete aNumbersContainer;
  }

int main()
  {
  int **bubbleSortNumbersContainer = getRandomNumbersContainer();

  std::cout << "Sorting " << CONTAINER_SIZE << " random numbers." << std::endl;
  std::cout << "======================================" << std::endl;

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== Before sorting ========" << std::endl;
      showNumbersContainer(bubbleSortNumbersContainer);
      }
  #endif // _DEBUG

  auto start = std::chrono::steady_clock::now();
  bubbleSort(bubbleSortNumbersContainer);
  auto end = std::chrono::steady_clock::now();

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== After sorting ========" << std::endl;
      showNumbersContainer(bubbleSortNumbersContainer);
      }
  #endif // _DEBUG

  std::cout << "Time of bubble sort: " << std::chrono::duration_cast<std::chrono::milliseconds>((end - start)).count() << "ms" << std::endl;

  // Free memory.
  removeNumbers(bubbleSortNumbersContainer);

  std::cout << "======================================" << std::endl;

  bubbleSortNumbersContainer = std::move(getRandomNumbersContainer());

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== Before sorting ========" << std::endl;
      showNumbersContainer(bubbleSortNumbersContainer);
      }
  #endif // _DEBUG

  start = std::chrono::steady_clock::now();
  bubbleSortUsingFlag(bubbleSortNumbersContainer);
  end = std::chrono::steady_clock::now();

  #ifdef _DEBUG
    if (CONTAINER_SIZE <= MIN_CONTAINER_SIZE)
      {
      std::cout << "======== After sorting ========" << std::endl;
      showNumbersContainer(bubbleSortNumbersContainer);
      }
  #endif // _DEBUG

  std::cout << "Time of bubble sort using flag: " << std::chrono::duration_cast<std::chrono::milliseconds>((end - start)).count() << "ms" << std::endl;

  return 0;
  }