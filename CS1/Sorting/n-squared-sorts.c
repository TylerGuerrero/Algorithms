#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RAND_VAL 1000

void swap(int *array, int i, int j)
{
  int temp;

  if (array == NULL)
    return;

  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// BUBBLE-SORT-STEPS
// 1) i = 0
// 2) loop through the array n - 1 times
// 3) if (array[i] > array[i + 1]) then swap(array, i, i + 1)
// 4) i++

// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
void bubble_sort(int *array, int n)
{
  int i, swapped;

  if (array == NULL || n == 0)
    return;

  swapped = 1;
  while (swapped)
  {
    swapped = 0;
    for (i = 0; i < n - 1; i++)
      if (array[i] > array[i + 1])
      {
        swap(array, i, i + 1);
        swapped = 1;
      }
  }
}

// BUBBLE-SORT-ENHANCED-STEPS
// 1) i = 0, j = 0
// 2) loop through the array n - 1 - j times
// 3) if (array[i] > array[i + 1]) then swap(array, i, i + 1)
// 4) i++, j++

// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
void bubble_sort_enhanced(int *array, int n)
{
  int i, j, swapped;

  if (array == NULL || n == 0)
    return;

  j = 0;
  swapped = 1;

  while (swapped)
  {
    swapped = 0;
    for (i = 0; i < n - 1 - j; i++)
      if (array[i] > array[i + 1])
      {
        swap(array, i, i + 1);
        swapped = 1;
      }
    j++;
  }
}

// SELECTION-SORT
// 1) i = 0
// 2) loop through the array n - 1 times
// 3) find the minimum element between minIndex = i and looped j = i + 1 it will
//    be stored in minIndex then swap(array, minIndex, i)
// 4) i++

// Big-O: Worst-Case: O(n^2), Best-Case: O(n^2), Space-Complexity: O(1)
void selection_sort(int *array, int n)
{
  int i, j, minIndex;

  if (array == NULL || n == 0)
    return;

  for (i = 0; i < n - 1; i++)
  {
    minIndex = i;
    for (j = i + 1; j < n; j++)
      if (array[j] < array[minIndex])
        minIndex = j;

    swap(array, minIndex, i);
  }
}

// INSERTION-SORT-STEPS
// 1) i = 1
// 2) loop through the array n times
// 3) take out the gap
// 4) if the gap_val < non_gap_val then start the scoothing processs
// 5) i++

// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
void insertion_sort(int *array, int n)
{
  int i, j, gap, val;

  if (array == NULL || n == 0)
    return;

  for (i = 0; i < n; i++)
  {
    gap = i;
    val = array[gap];

    for (j = gap - 1; j >= 0 && val < array[j]; j--)
    {
      array[j + 1] = array[j];
      gap--;
    }
    array[gap] = val;
  }
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
int *create_array(int n)
{
  int i;
  int *array;

  if (n == 0)
    return NULL;

  array = malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND_VAL + 1;

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
  printf("\n");
}

int main(void)
{
  int n = 12;
  int *array1, *array2, *array3;

  srand(time(NULL));

  array1 = create_array(n);
  array2 = create_array(n);
  array3 = create_array(n);

  // Bubble Sort
  printf("Bubble Sort:\n");
  print_array(array1, n);
  bubble_sort(array1, n);
  print_array(array1, n);
  printf("\n");

  // Selection Sort
  printf("Selection Sort:\n");
  print_array(array2, n);
  selection_sort(array2, n);
  print_array(array2, n);
  printf("\n");


  // Insertion Sort
  printf("Insertion Sort:\n");
  print_array(array3, n);
  insertion_sort(array3, n);
  print_array(array3, n);
  printf("\n");

  free(array1);
  free(array2);
  free(array3);
  return 0;
}
