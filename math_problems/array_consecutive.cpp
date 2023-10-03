#include <assert.h>
#include <iostream>

bool isConsecutive(int arr[], int size)
{
  int minValue = arr[0];
  int maxValue = arr[0];
  int sum = arr[0];
  for (int i = 1; i < size; ++i) {
    sum += arr[i];

    if (arr[i] < minValue) {
      minValue = arr[i];
    }

    if (arr[i] > maxValue) {
      maxValue = arr[i];
    }
  }

  if (((maxValue - minValue + 1) == size) && (sum == (0.5 * (minValue + maxValue) * size))) {
    return true;
  } else {
    return false;
  }

  return false;
}

int main()
{
  int arr[] = {5, 2, 3, 1, 4};
  const int size = sizeof(arr) / sizeof(arr[0]);
  if (isConsecutive(arr, size)) {
    std::cout << "Array elements are consecutive" << std::endl;
  } else {
    std::cout << "Array elements are not consecutive" << std::endl;
  }

  return 0;
}