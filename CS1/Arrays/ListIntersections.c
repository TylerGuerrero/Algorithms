#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RAND_VAL 1000

// Big-O: Worst-Case: O(n), Best-Case: O(1), Space-Complexity: O(1)
int linear_search(int *array, int n, int key)
{
  int i;

  if (array == NULL || n == 0)
    return 0;

  for (i = 0; i < n; i++)
    if (array[i] == key)
      return 1;

  return 0;
}

// Big-O: Worst-Case: O(logn), Best-Case: O(1), Space-Complexity: O(1)
int binary_search(int *array, int n, int key)
{
  int lo, mid, hi;

  if (array == NULL || n == 0)
    return 0;

  lo = 0;
  hi = n - 1;

  // case for even or odd length array
  while (lo <= hi)
  {
    mid = lo + (hi - lo) / 2;

    if (key < array[mid])
      hi = mid - 1;
    else if (key > array[mid])
      lo = mid + 1;
    else
      return 1;
  }

  return 0;
}

int my_compare (const void *a, const void *b)
{
  return (*(int*)a - *(int*)b);
}

// Big-O: Worst-Case: O(n^2), Best-Case: O(nlogn), Space-Complexity: O(n)
int *create_sorted_array(int n)
{
  int i;
  int *array;

  if (n == 0)
    return NULL;

  array = malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND_VAL + 1;

  qsort(array, n, sizeof(int), my_compare);
  return array;
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
int *create_sorted_array_fancy(int n)
{
  int i;
  int *array;

  if (n == 0)
    return NULL;

  array = malloc(sizeof(int) * n);
  array[0] = rand() % MAX_RAND_VAL + 1;

  for (i = 1; i < n; i++)
    array[i] = array[i - 1] + rand() % MAX_RAND_VAL + 1;

  return array;
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
void print_array(int *array, int n)
{
  int i;

  if (array == NULL || n == 0)
    return;

  for (i = 0; i < n; i++)
    printf("%d ", array[i]);

  printf("\n\n");
}

// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
void print_list_intersection(int *array1, int len1, int *array2, int len2)
{
  int i;

  if (array1 == NULL || len1 == 0 || array2 == NULL || len2 == 0)
    return;

  for (i = 0; i < len1; i++)
    if (linear_search(array2, len2, array1[i]))
      printf("Both array's just intersected with values %d\n", array1[i]);

  printf("\n\n");
}

// Big-O: Worst-Case: O(nlogn), Best-Case: O(n), Space-Complexity: O(1)
void print_list_intersection_fancy(int *array1, int len1, int *array2, int len2)
{
  int i;

  if (array1 == NULL || len1 == 0 || array2 == NULL || len2 == 0)
    return;

  for (i = 0; i < len1; i++)
    if (binary_search(array2, len2, array1[i]))
      printf("Both array's just intersected with values %d\n", array1[i]);

  printf("\n\n");
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
void print_list_intersection_fanciest(int *array1, int len1, int *array2, int len2)
{
  int i, j;

  if (array1 == NULL || len1 == 0 || array2 == NULL || len2 == 0)
    return;

  i = j = 0;

  // && cause their wont be anymore left that will intersect
  while (i < len1 && j < len2)
  {
    if (array1[i] < array2[j])
      i++;
    else if (array1[i] > array2[j])
      j++;
    else
    {
      printf("Both array's just intersected with values %d\n", array1[i]);
      i++;
      j++;
    }
  }

  printf("\n\n");
}

// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
int canMakeSum(int *array, int n, int key)
{
  int i;

  if (array == NULL || n == 0)
    return 0;

  for (i = 0; i < n; i++)
    if (linear_search(array, n, key - array[i]))
      return 1;

  return 0;
}

// Big-O: Worst-Case: O(nlogn), Best-Case: O(n), Space-Complexity: O(1)
int canMakeSumFancy(int *array, int n, int key)
{
  int i;

  if (array == NULL || n == 0)
    return 0;

  for (i = 0; i < n; i++)
    if (binary_search(array, n, key - array[i]))
      return 1;

  return 0;
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
int canMakeSumFanciest(int *array, int n, int key)
{
  int i, j;

  if (array == NULL || n == 0)
    return 0;

  i = 0;
  j = n - 1;

  while (i < j)
  {
    int sum = array[i] + array[j];

    if (sum < key)
      i++;
    else if (sum > key)
      j--;
    else
      return 1;
  }

  return 0;
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
int keyCounter(int *array, int n, int key)
{
  int i, cnt;

  if (array == NULL || n == 0)
    return 0;

  cnt = 0;
  for (i = 0; i < n; i++)
    if (array[i] == key)
      cnt++;

  return cnt;
}

// Big-O: Worst-Case: O(logn + n), Best-Case: O(logn), Space-Complexity: O(1)
int keyCounterFancy(int *array, int n, int key)
{
  int lo, mid, hi;
  int left, right, cnt;

  if (array == NULL || n == 0)
    return 0;

  lo, cnt, left, right = 0;
  hi = n - 1;

  // case
  while (lo <= hi)
  {
    mid = lo + (hi - lo) / 2;

    if (key < array[mid])
      hi = mid - 1;
    else if (key > array[mid])
      lo = mid + 1;
    else
    {
      left = mid - 1;
      while (left >= 0 && array[left] == key)
      {
        left--;
        cnt++;
      }

      right = mid;
      while (right < n && array[right] == key)
      {
        right++;
        cnt++;
      }

      return cnt;
    }
  }

  return 0;
}

int keyCounterFanciest(int *array, int n, int key)
{
  if (array == NULL || n == 0)
    return 0;
}

int main(void)
{
  int *array1, *array2, n, i;

	printf("How many integers shall we generate? ");
	scanf("%d", &n);

	srand(time(NULL));

	// Create and print two sorted arrays of random integers.
	array1 = create_sorted_array(n);
	array2 = create_sorted_array(n);

	printf("array1:\n");
	print_array(array1, n);

	printf("array2:\n");
	print_array(array2, n);

	// Call our various list intersection functions.
	printf("List Intersection:\n");
	print_list_intersection(array1, n, array2, n);

	printf("List Intersection:\n");
	print_list_intersection_fancy(array1, n, array2, n);

	printf("List Intersection:\n");
	print_list_intersection_fanciest(array1, n, array2, n);

	// Clean up after yourself.
	free(array1);
	free(array2);

	return 0;
}
