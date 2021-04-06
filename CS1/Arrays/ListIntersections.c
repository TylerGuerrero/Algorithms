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
    printf("%d", array[i]);

  printf("\n\n");
}

// Big-O: Worst-Case: O(n^2), Best-Case: O(n^2), Space-Complexity: O(1)
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

// Big-O: Worst-Case: O(nlogn), Best-Case: O(nlogn), Space-Complexity: O(1)
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
