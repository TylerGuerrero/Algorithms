#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// MERGE-SORT-STEPS
// 1) if (lo >= hi) return case if for a single element
// 2) set mid, i, j, k
// 3) Recursively split the array into the left half and right half
// 4) Create an aux array of size (hi - lo + 1)
// 5) Merge the sorted left subarray and the right sorted subarray into the aux array
// 6) map the aux array into its correct positions in the original array

// Big-O: Worst-Case: O(nlogn), Best-Case: O(nlogn), Space-Complexity: O(n)
void MergeSort(int *array, int lo, int hi)
{
  int i, j, k, mid;
  int  *aux;

  // case for single element
  if (lo >= hi)
    return;

  mid = lo + (hi - lo) / 2;
  i = lo;
  j = mid + 1;
  k = 0;

  MergeSort(array, lo, mid);
  MergeSort(array, mid + 1, hi);

  aux = malloc(sizeof(int) * (hi - lo + 1));

  while (i <= mid || j <= hi)
  {
    if (i > mid)
      aux[k++] = array[j++];
    else if (j > hi)
      aux[k++] = array[i++];
    else if (array[i] < array[j])
      aux[k++] = array[i++];
    else
      aux[k++] = array[j++];
  }

  for (i = lo; i <= hi; i++)
    array[i] = aux[i - lo];

  free(aux);
}

void printArray(int *array, int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d%c", array[i], (i == n - 1) ? '\n' : ' ');
}

// Returns 1 if the array is sorted, 0 otherwise.
int isSorted(int *array, int n)
{
	int i;

	for (i = 0; i < n - 1; i++)
		if (array[i] > array[i + 1])
			return 0;

	return 1;
}

int main(int argc, char **argv)
{
	int i, n, *array;
	srand(time(NULL));

	if (argc < 2)
	{
		fprintf(stderr, "Proper syntax: %s <n>\n", argv[0]);
		return 1;
	}

	// Array length is passed in as a command line argument.
	n = atoi(argv[1]);
	array = malloc(sizeof(int) * n);

	// Populate our array with random numbers on the range [1, 1000].
	for (i = 0; i < n; i++)
		array[i] = rand() % 1000 + 1;

	// Print the unsorted array.
	printf("\nUnsorted array:\n");
	printArray(array, n);

	// Sort the array.
	MergeSort(array, 0, n - 1);

	// Print the sorted array.
	printf("\nSorted array:\n");
	printArray(array, n);

	printf("\n%s\n", isSorted(array, n) ? "HOORAY!" : "fail whale :(");

	// Clean up after yourself.
	free(array);

	return 0;
}
