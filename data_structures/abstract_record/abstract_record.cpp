#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

namespace
{
  constexpr int MIN_INTEGER = -1000;
  constexpr int MAX_INTEGER = 9000;

  constexpr int MIN_CHAR_CODE = 66; // 'B'
  constexpr int MAX_CHAR_CODE = 83; // 'S'

  constexpr float MIN_REAL_NUMBER = 1001.0f;

  constexpr int PRINT_COUNT = 20;
  constexpr auto FILE_NAME_TXT = "input.txt";
} // namespace

struct Record
{
  int theIntegerNumber;
  float theRealNumber;
  char theLetter;

  Record() = default;
  Record(int aIntegerNumber, float aRealNumber, char aLetter);
};

Record::Record(int aIntegerNumber, float aRealNumber, char aLetter):
  theIntegerNumber(aIntegerNumber),
  theRealNumber(aRealNumber),
  theLetter(aLetter)
{
}

Record** generate(int aSize)
{
  std::random_device randomDevice;
  std::default_random_engine randomEngine(randomDevice());

  std::uniform_int_distribution<int> integerRange(MIN_INTEGER, MAX_INTEGER);
  std::uniform_real_distribution<float> letterRange(MIN_CHAR_CODE, MAX_CHAR_CODE);

  if (aSize > 0)
  {
    Record** records = new Record*[aSize];
    for (int i = 0; i < aSize; i++)
    {
      records[i] =
        new Record(integerRange(randomEngine), MIN_REAL_NUMBER + i, static_cast<char>(letterRange(randomEngine)));
    }

    return records;
  }
  else
  {
    return nullptr;
  }
}

void removeRecords(Record** aRecords, int aSize)
{
  if (aRecords)
  {
    for (int i = 0; i < aSize; i++)
    {
      delete aRecords[i];
    }
  }

  delete[] aRecords;
}

void sort(Record** aRecords, int aSize)
{
  // Using bubble sort;

  // std::cout << "Before sort" << std::endl;
  // show(aRecords);

  if (aRecords)
  {
    for (int i = 0; i < aSize; i++)
    {
      for (int j = i; j < aSize; j++)
      {
        if ((aRecords[i]->theIntegerNumber) > (aRecords[j]->theIntegerNumber))
        {
          Record tmp = *aRecords[j];
          *aRecords[j] = *aRecords[i];
          *aRecords[i] = tmp;
        }
      }
    }

    // std::cout << "After sort" << std::endl;
    // show(aRecords);
  }
}

int countSigns(Record** aRecords, int aCount, char aSign)
{
  int count = 0;
  if (aRecords)
  {
    for (int i = 0; i < aCount; i++)
    {
      if (aRecords[i]->theLetter == aSign)
      {
        count++;
      }
    }
  }

  return count;
}

void show(Record** aRecords)
{
  for (int i = 0; i < PRINT_COUNT; i++)
  {
    std::cout << aRecords[i]->theIntegerNumber << "  ";
  }
  std::cout << std::endl;
}

int main()
{
  clock_t begin = clock();
  int N;
  char X;

  try
  {
    std::ifstream file(FILE_NAME_TXT, std::ios::in);
    if (file.good() && file.is_open())
      file >> N >> X;

    file.close();
  }
  catch (const std::exception& ex)
  {
    throw std::logic_error(ex.what());
  }

  Record** records = generate(N);
  sort(records, N);

  for (int i = 0; i < PRINT_COUNT; i++)
    std::cout << records[i]->theIntegerNumber << "," << records[i]->theRealNumber << "," << records[i]->theLetter
              << std::endl;

  int count = countSigns(records, N, X);
  removeRecords(records, N);

  clock_t end = clock();
  double timeSpent = (static_cast<double>(end) - static_cast<double>(begin)) / CLOCKS_PER_SEC;

  std::cout << count << std::endl;
  std::cout << timeSpent << std::endl;

  return EXIT_SUCCESS;
}