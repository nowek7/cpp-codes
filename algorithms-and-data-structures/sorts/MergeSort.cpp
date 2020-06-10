#include <chrono>
#include <random>
#include <iostream>

constexpr int CONTAINER_SIZE = 100'000;
constexpr int MIN_CONTAINER_SIZE = 10;

int **getRandomNumberContainer()
  {
  std::random_device device;
  std::mt19937_64 engine(device());
  std::uniform_int_distribution<int> distrubution(-100, 100);

  int **numberContainer = new int *[CONTAINER_SIZE];
  for (int i = 0; i < CONTAINER_SIZE; i++)
    numberContainer[i] = new int(distrubution(engine));

  return numberContainer;
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

void merge(int **aNumbersContainer, int &aStartIndex, int &aMiddleIndex, int &aEndIndex)
  {
  int size = aEndIndex - aStartIndex + 1;
  int **copyContainer = new int *[size];
  for (int i = 0; i < size; i++)
    copyContainer[i] = new int(*aNumbersContainer[aStartIndex + i]);

  int startIndex = aStartIndex;
  int middleIndex = aMiddleIndex + 1;
  for (int i = aStartIndex; i <= aEndIndex; i++)
    {
    if (startIndex > aMiddleIndex)
      {
      *aNumbersContainer[i] = *copyContainer[middleIndex - aStartIndex];
      middleIndex++;
      }
    else if (middleIndex > aEndIndex)
      {
      *aNumbersContainer[i] = *copyContainer[startIndex - aStartIndex];
      startIndex++;
      }
    else if (*copyContainer[middleIndex - aStartIndex] < *copyContainer[startIndex - aStartIndex])
      {
      *aNumbersContainer[i] = *copyContainer[middleIndex - aStartIndex];
      middleIndex++;
      }
    else
      {
      *aNumbersContainer[i] = *copyContainer[startIndex - aStartIndex];
      startIndex++;
      }
    }

  removeNumbers(copyContainer, size);
  }

void mergeSort(int **aNumbersContainer, int aStartIndex, int aEndIndex)
  {
  if (aStartIndex < aEndIndex)
    {
    int middleIndex = static_cast<int>((aEndIndex + aStartIndex) * 0.5);

    mergeSort(aNumbersContainer, aStartIndex, middleIndex);
    mergeSort(aNumbersContainer, middleIndex + 1, aEndIndex);
    merge(aNumbersContainer, aStartIndex, middleIndex, aEndIndex);
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
  mergeSort(numbersContainer, 0, CONTAINER_SIZE - 1);
  auto end = std::chrono::steady_clock::now();

  std::cout << "Time of merge sort: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

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