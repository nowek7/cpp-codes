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

void quickSort(int *aNumbersContainer, int aStartIndex, int aEndIndex)
  {
  int i = aStartIndex;
  int j = aEndIndex;
  const int middleIndex = static_cast<int>((aStartIndex + aEndIndex) * 0.5);
  int value = aNumbersContainer[middleIndex];

  do
    {
    while (aNumbersContainer[i] < value)
      i++;

    while (aNumbersContainer[j] > value)
      j--;

    if (i <= j)
      {
      auto temp = aNumbersContainer[j];
      aNumbersContainer[j] = aNumbersContainer[i];
      aNumbersContainer[i] = temp;

      i++;
      j--;
      }

    if (aStartIndex < j)
      quickSort(aNumbersContainer, aStartIndex, j);
    if (i < aEndIndex)
      quickSort(aNumbersContainer, i, aEndIndex);
    }
  while (i <= j);
  }

int main()
  {
  int *numbersContainer = getRandomNumberContainer();

  #ifdef _DEBUG
    std::cout << "======== Before sorting ========" << std::endl;
    showNumberContainer(numbersContainer);
  #endif // _DEBUG

  auto start = std::chrono::steady_clock().now();
  quickSort(numbersContainer, 0, CONTAINER_SIZE - 1);
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