#include <chrono>
#include <random>
#include <iostream>

constexpr int CONTAINER_SIZE = 10;

int *getRandomNumberContainer()
  {
  std::random_device device;
  std::mt19937_64 engine(device());
  std::uniform_int_distribution<int> distrubution(-100, 100);

  int *numbersContainer = new int[CONTAINER_SIZE];
  for (int i = 0; i < CONTAINER_SIZE; i++)
    numbersContainer[i] = distrubution(engine);

  return numbersContainer;
  }

void showNumberContainer(int *aNumbersContainer)
  {
  for (int i = 0; i < CONTAINER_SIZE - 1; i++)
    std::cout << aNumbersContainer[i] << ", ";
  std::cout << aNumbersContainer[CONTAINER_SIZE - 1] << std::endl;
  }

void removeNumbers(int *aNumbersContainer)
  {
  // Free memory.
  delete[] aNumbersContainer;
  }

void selectionSort(int *aNumbersContainer)
  {
  auto findIndex = [aNumbersContainer](int &aStartIndex)
    {
    auto index = aStartIndex;
    for (int i = aStartIndex + 1; i < CONTAINER_SIZE; i++)
      {
      if (aNumbersContainer[index] > aNumbersContainer[i])
        index = i;
      }

    return index;
    };

  for (int i = 0; i < CONTAINER_SIZE; i++)
    {
    auto index = findIndex(i);

    auto temp = aNumbersContainer[i];
    aNumbersContainer[i] = aNumbersContainer[index];
    aNumbersContainer[index] = temp;
    }
  }

int main()
  {
  int *numbersContainer = getRandomNumberContainer();

  #ifdef _DEBUG
  std::cout << "======== Before sorting ========" << std::endl;
  showNumberContainer(numbersContainer);
  #endif // _DEBUG

  auto start = std::chrono::steady_clock().now();
  selectionSort(numbersContainer);
  auto end = std::chrono::steady_clock().now();

  auto timeSort = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  std::cout << "Time of quick sort: " << timeSort << " microseconds." << std::endl;

  #ifdef _DEBUG
  std::cout << "======== After sorting ========" << std::endl;
  showNumberContainer(numbersContainer);
  #endif // _DEBUG

  removeNumbers(numbersContainer);

  return 0;
  }