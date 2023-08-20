#include "my_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20

#define LEFT_BOUND -10
#define INTERVAL_SIZE 20

void printSeparator(const char* label)
{
	printf("***************%s***************\n", label);
}

void printArray(int* array, const int size)
{
	if (!array)
		return;

	for (int i = 0; i < size; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

int* randomArray(const int size)
{
	if (size <= 0)
		return NULL;

	int *array = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		array[i] = (rand() % (INTERVAL_SIZE) + LEFT_BOUND);
	}

	return array;
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	printSeparator("BUBBLE_SORT");
	int *array = randomArray(ARRAY_SIZE);
	printArray(array, ARRAY_SIZE);
	bubble_sort(array, ARRAY_SIZE);
	printSeparator("AFTER");
	printArray(array, ARRAY_SIZE);

	free(array);
	array = NULL;

	printSeparator("SELECTION_SORT");
	array = randomArray(ARRAY_SIZE);
	printArray(array, ARRAY_SIZE);
	selection_sort(array, ARRAY_SIZE);
	printSeparator("AFTER");
	printArray(array, ARRAY_SIZE);

	free(array);
	array = NULL;

	printSeparator("INSERTION_SORT");
	array = randomArray(ARRAY_SIZE);
	printArray(array, ARRAY_SIZE);
	insertion_sort(array, ARRAY_SIZE);
	printSeparator("AFTER");
	printArray(array, ARRAY_SIZE);
	free(array);

	return 0;
}
