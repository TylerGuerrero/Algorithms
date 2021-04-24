#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RAND_VAL 1000

// BUCKET-SORTS STEPS
// 1) find the max element in the array
// 2) create the buckets array of size max + 1 and set all the values in the array to 0
// 3) map the elements in the array to the index's of the bucket array and increment
// 4) loop through the buckets array and insert the values into the array at index 0
//    the val of the bucket array > 0.

// Big-O: O(n + m), Space_Complexity: O(n)
void buckets_sort(int *array, int n)
{
  int i, j, max;
  int *buckets;

  if (array == NULL)
    return;

  max = array[0];
  for (i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];

  buckets = calloc(max + 1, sizeof(int));

  for (i = 0; i < n; i++)
    buckets[array[i]]++;

  for (i = j = 0; i <= max; i++)
  {
    while (buckets[i] > 0)
    {
      array[j++] = i;
      --buckets[i];
    }
  }

  free(buckets);
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
  int *array;
  int n = 12;

  srand(time(NULL));

  array = create_array(n);

  printf("Bucket Sort\n");
  print_array(array, n);
  buckets_sort(array, n);
  print_array(array, n);

  free(array);
}
