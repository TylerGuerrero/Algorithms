#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fib sequence 0, 1, 1, 2, 3, 5, 13 etc...
// base cases fib(0) = 0, fib(1) = 1

// Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space-Complexity: O(n)
int fib(int n)
{
  if (n < 2)
    return n;

  return fib(n - 1) + fib(n - 2);
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
int fib_optimized(int n)
{
  int *array;
  int i, result;

  if (n  < 2)
    return n;

  array = malloc(sizeof(int) * (n + 1));

  array[0] = 0;
  array[1] = 1;

  for (i = 2; i <= n; i++)
    array[i] = array[i - 1] + array[i - 2];

  result = array[n];
  free(array);
  return result;
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
int fib_super_optimized(int n)
{
  int i;
  int array[2];

  if (n < 2)
    return n;

  array[0] = 0;
  array[1] = 1;

  for (i = 2; i <= n; i++)
    array[i % 2] = array[1] + array[0];

  return array[n % 2];
}

int main(void)
{
  printf("%d\n", fib(44));
  printf("%d\n", fib_optimized(44));
  printf("%d\n", fib_super_optimized(44));
}
