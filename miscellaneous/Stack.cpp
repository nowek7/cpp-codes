#include <iostream>
#include <vector>
#include <random>

struct Box
  {
  double *theValue = nullptr;
  Box *theNext = nullptr;

  Box() = default;
  Box(double &aValue);
  ~Box();
  };

Box::Box(double &aValue)
  :
  theValue(new double(aValue))
  {}

Box::~Box()
  {
  if (theValue)
    delete theValue;

  if (theNext)
    delete theNext;
  }

// Init stack;
Box *box = nullptr;

void pushToStack(double &aValue)
  {
  Box *newBox = new Box(aValue);

  if (box)
    newBox->theNext = box;

  box = newBox;
  }

double popFromStack()
  {
  if (box)
    {
    double value = *box->theValue;
    box = box->theNext;

    return value;
    }
  else
    throw std::logic_error("Stack is empty!");
  }

bool stackIsEmpty()
  {
  if (box)
    return false;
  else
    return true;
  }

std::vector<double> getStackValues()
  {
  std::vector<double> values;
  if (box)
    {
    values.push_back(*box->theValue);
    auto next = box->theNext;
    while (next)
      {
      values.push_back(*next->theValue);
      next = next->theNext;
      }
    }

  return values;
  }

int getStackSize()
  {
  int size = 0;
  if (box)
    {
    size++;
    auto next = box->theNext;
    while (next)
      {
      size++;
      next = next->theNext;
      }
    }

  return size;
  }

double getRandomNumber()
  {
  std::random_device device;
  std::mt19937_64 engine(device());
  std::uniform_real_distribution<double> distrubution(-10.0, 10.0);

  return distrubution(engine);
  }

void menu()
  {
  std::cout << std::endl;
  std::cout << "-------OPERATION ON STACK-------" << std::endl;
  std::cout << "1. Push value to stack." << std::endl;
  std::cout << "2. Check if stack is empty." << std::endl;
  std::cout << "3. Remove value from stack." << std::endl;
  std::cout << "4. Show values in stack." << std::endl;
  std::cout << "5. Show size of stack." << std::endl;
  std::cout << "100. Exit." << std::endl;
  std::cout << std::endl;
  }

int main()
  {
  int count = 0;
  int numberOfOperation;
  bool runProgram = true;
  while (runProgram)
    {
    if (count % 3 == 0)
      menu();

    std::cout << "Operation: ";
    std::cin >> numberOfOperation;

    switch (numberOfOperation)
      {
        case 1:
          {
          double value = getRandomNumber();
          pushToStack(value);

          std::cout << "Pushed 1 elements to stack!" << std::endl;
          break;
          }

        case 2:
          {
          if (stackIsEmpty())
            std::cout << "Stack is empty!" << std::endl;
          else
            std::cout << "Stack is not empty!" << std::endl;

          break;
          }

        case 3:
          {
          if (!stackIsEmpty())
            {
            auto removed = popFromStack();
            std::cout << "Removed value from stack: " << removed << std::endl;
            }
          else
            std::cout << "Stack is empty. There is nothing to delete!" << std::endl;

          break;
          }

        case 4:
          {
          if (!stackIsEmpty())
            {
            auto values = getStackValues();
            for (auto &value : values)
              std::cout << value << " ";
            std::cout << std::endl;
            }
          else
            std::cout << "Stack is empty!" << std::endl;

          break;
          }

        case 5:
          std::cout << "Stack has " << getStackSize() << " elements." << std::endl;
          break;

        case 100:
          runProgram = false;
          break;

        default:
          std::cout << "Error. Try again!" << std::endl;
          break;
      }

    count++;
    }

  // Free memory.
  delete box;

  return 0;
  }
