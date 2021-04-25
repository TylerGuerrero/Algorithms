#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *array, int i, int j)
{
  int temp;

  if (array == NULL)
    return;

  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// Big-O: O(n), Space-Complexity: O(1)
void printArray(int *array, int n)
{
  int i;

  if (array == NULL)
    return;

  for (i = 0; i < n; i++)
    	printf("%d%c", array[i], (i == n - 1) ? '\n' : ' ');
}

// Big-O: O(n), Space-Complexity: O(1)
int partition(int *array, int lo, int hi, int pivot)
{
  if (array == NULL)
    return INT_MIN;

  while (lo <= hi)
  {
    while (array[lo] < pivot)
      lo++;

    while (array[hi] > pivot)
      hi--;

    if (lo <= hi)
    {
      swap(array, lo, hi);
      lo++; hi--;
    }
  }

  return lo;
}

// QUICK-SORT-STEPS
// 1) if (lo >= hi) return
// 2) set pivot
// 3) set index from partition
// 4) Recursively split the array into the left half then the right half

// Big-O: Worst-Case: O(n^2), Best-Case: O(nlogn), Space-Complexity: O(logn)
void QuickSort(int *array, int lo, int hi)
{
  if (array == NULL)
    return;

  if (lo >= hi)
    return;

  int pivot = array[lo + (hi - lo) / 2];
  int index = partition(array, lo, hi, pivot);
  QuickSort(array, lo, index - 1);
  QuickSort(array, index, hi);
}

int main(void)
{
  int i, n;
  int *array;

  n = 17;
  array = malloc(sizeof(int) * n);

	// Populate our array with random numbers on the range [1, 1000].
	for (i = 0; i < n; i++)
		array[i] = rand() % 1000 + 1;

  // Print the unsorted array.
	printf("Unsorted array:\n");
	printArray(array, n);

	// Sort the array.
	QuickSort(array, 0, n - 1);

	// Print the sorted array.
	printf("\nSorted array:\n");
	printArray(array, n);
  free(array);

  return 0;
}
