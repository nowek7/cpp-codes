#include "my_sort.h"

void swap(int* lhs, int* rhs)
{
  // Avoid swaps the same value. (selection sort)
  if (lhs != rhs)
  {
    (*rhs) = (*lhs) + (*rhs);
    (*lhs) = (*rhs) - (*lhs);
    (*rhs) = (*rhs) - (*lhs);
  }
}

void bubble_sort(int* array, int size)
{
  if (array && size > 0)
  {
    // for (int i = 0 ; i < size; i++)
    // {
    //   for (int j = 0; j < size - 1; j++)
    //   {
    //     if (array[j] > array[j + 1])
    //     {
    //       swap(&array[j], &array[j + 1]);
    //     }
    //   }
    // }

    // Optimized version with flag.
    int sorted = 0;
    for (int i = 0; i < size && !sorted; ++i)
    {
      sorted = 1;
      for (int j = 0; j < size - 1 - i; ++j)
      {
        if (array[j] > array[j + 1])
        {
          sorted = 0;
          swap(&array[j], &array[j + 1]);
        }
      }
    }
  }
}

void selection_sort(int* array, int size)
{
  if (array && size > 0)
  {
    int idx;
    for (int i = 0; i < size; ++i)
    {
      // Find index of minimum value.
      idx = i;
      for (int j = i + 1; j < size; ++j)
      {
        if (array[j] < array[idx])
        {
          idx = j;
        }
      }

      swap(&array[i], &array[idx]);
    }
  }
}

void insertion_sort(int* array, int size)
{
  if (array && size > 0)
  {
    for (int i = 1; i < size; ++i)
    {
      for (int j = i; j > 0; --j)
      {
        if (array[j] < array[j - 1])
        {
          swap(&array[j], &array[j - 1]);
        }
      }
    }
  }
}
