#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Heap
{
  int *array;
  int size;
  int capacity;
} Heap;

#define GENRIC_HEAP_SUCCESS INT_MAX
#define GENRIC_HEAP_FAILURE INT_MIN

Heap *createHeap(int capacity)
{
  Heap *h = malloc(sizeof(Heap));
  h->array = malloc(sizeof(int) * capacity);
  h->size = 0;
  h->capacity = capacity;
  return h;
}

Heap *destroyHeap(Heap *h)
{
  if (h == NULL)
    return NULL;
  else if (h->array == NULL)
  {
    free(h);
    return NULL;
  }
  else
  {
    free(h->array);
    free(h);
    return NULL;
  }
}

int isEmpty(Heap *h)
{
  return (h == NULL || h->size == 0);
}

int isFull(Heap *h)
{
  return (h == NULL || h->size == h->capacity);
}

void swap(int *array, int i, int j)
{
  int temp;

  if (array == NULL)
    return;

  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

int getParent(int child)
{
  return ((child - 1) / 2);
}

// Big-O: Worst-Case: O(logn), Best-Case: O(1)
void perculateUp(Heap *h, int child)
{
  int parent = getParent(child);

  while (h->array[child] > h->array[parent])
  {
    swap(h->array, child, parent);
    child = parent;
    parent = getParent(child);
  }
}

// Big-O: Worst-Case: O(logn), Best-Case: O(1)
int heapInsert(Heap *h, int child)
{
  if (isFull(h))
    return GENRIC_HEAP_SUCCESS;

  h->array[h->size++] = child;
  perculateUp(h, h->size - 1);
  return GENRIC_HEAP_SUCCESS;
}

int indexOfBiggerChild(Heap *h, int parent)
{
  int lc, rc;

  lc = ((parent * 2 + 1) >= h->size) ? parent : parent * 2 + 1;
  rc = ((parent * 2 + 2) >= h->size) ? parent : parent * 2 + 2;

  return (h->array[lc] > h->array[rc]) ? lc : rc;
}

// Big-O: Worst-Case: O(logn), Best-Case: O(1)
void perculateDown(Heap *h, int parent)
{
  int child = indexOfBiggerChild(h, parent);

  while (h->array[parent] < h->array[child])
  {
    swap(h->array, child, parent);
    parent = child;
    child = indexOfBiggerChild(h, parent);
  }
}

// Big-O: Worst-Case: O(logn), Best-Case: O(1)
int deleteMax(Heap *h)
{
  int retval;

  if (isEmpty(h))
    return GENRIC_HEAP_SUCCESS;

  retval = h->array[0];
  h->array[0] = h->array[--h->size];
  perculateDown(h, 0);
  return retval;
}

int find_max(Heap *h)
{
  if (isEmpty(h))
    return GENRIC_HEAP_FAILURE;

  return h->array[0];
}

int last_parent_with_at_least_child(int size)
{
  return (getParent(size - 1));
}

void printHeap(Heap *h)
{
  int i;

  if (isEmpty(h))
    return;

  for (i = 0; i < h->size; i++)
    printf("%d ", h->array[i]);

  printf("\n\n");
}


int main(void)
{
  int i, r, n = 10;
  Heap *heapyHeap = createHeap(n);

  srand(time(NULL));

  // Insert some random integers into the heap.
  for (i = 0; i < n; i++)
  {
    printf("Inserting %d...\n", r = rand() % 50 + 1);
    heapInsert(heapyHeap, r);
  }

  // Delete the minimum element from the heap until it's empty. This should
  // print all the integers out in sorted order.
  printf("\nResult of heapsort: ");
  for (i = 0; i < n; i++)
  {
    printf("%d%c", deleteMax(heapyHeap), i == (n - 1) ? '\n' : ' ');
    //printHeap(heapyHeap);
    // Exercise: Write a printHeap() function that prints the array inside
    // the heap struct, and call it here so you can see how the array is
    // changing with each deleteMin() operation. Perform the deleteMin()
    // operation on paper and verify that your results are the same.
  }

  heapyHeap = destroyHeap(heapyHeap);
  return 0;
}
