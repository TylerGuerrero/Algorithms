#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sum(int n)
{
  if (n == 0)
    return 0;

  return n + sum(n - 1);
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

// coming from the back of the array
int find_min_array(int *array, int n)
{
  if (array == NULL || n == 0)
    return INT_MIN;
  else if (n == 1)
    return array[0];
  else
    return min(array[n - 1], find_min_array(array, n - 1));
}

// coming from the front of the array
int find_min_array_fancy(int *array, int n)
{
  if (array == NULL || n == 0)
    return INT_MIN;
  else if (n == 1)
    return array[0];
  else
    return min(array[0], find_min_array_fancy(array + 1, n - 1));
}

int find_min_array_super_fancy(int *array, int n)
{
  return ((n == 1) ? array[0] : min(array[0], find_min_array_super_fancy(array + 1, n - 1)));
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

// coming from the back of the array
int find_max_array(int *array, int n)
{
  if (array == NULL || n == 0)
    return INT_MIN;
  else if (n == 1)
    return array[0];
  else
    return max(array[n - 1], find_max_array(array, n - 1));
}

// coming from the front of the array
int find_max_array_fancy(int *array, int n)
{
  if (array == NULL || n == 0)
    return INT_MIN;
  else if (n == 1)
    return array[0];
  else
    return max(array[0], find_max_array_fancy(array + 1, n - 1));
}

int find_max_array_super_fancy(int *array, int n)
{
  return (n == 1) ? array[0] : max(array[n - 1], find_max_array_super_fancy(array, n - 1));
}

int factorial(int n)
{
  if (n == 0)
    return 1;

  return n * factorial(n - 1);
}

int mult(int a, int b)
{
  if (a == 0 || b == 0)
    return 0;

  return a + mult(a, b - 1);
}

void print_string(char *str, int n)
{
  if (str == NULL || n == 0)
  {
    printf("\n");
    return;
  }

  printf("%c", *str);
  print_string(str + 1, n - 1);
}

void print_string_alternative(char *str, int n)
{
  if (str == NULL || n == 0)
  {
    printf("\n");
    return;
  }

  print_string_alternative(str, n - 1);
  printf("%c", str[n - 1]);
}

void print_string_fancy(char *str)
{
  if (*str == '\0')
  {
    printf("\n");
    return;
  }

  printf("%c", *str);
  print_string_fancy(str + 1);
}

void print_string_reverse(char *str, int n)
{
  if (str == NULL || n == 0)
  {
    printf("\n");
    return;
  }

  printf("%c", str[n - 1]);
  print_string_reverse(str, n - 1);
}

void print_string_reverse_fancy(char *str, int n, int len)
{
  if (str == NULL || n == 0)
    return;

  print_string_reverse_fancy(str + 1, n - 1, len);
  printf("%c", *str);

  if (len == n)
    printf("\n");
}

unsigned int power(int a, int n)
{
  if (n == 0)
    return 1;
  if (a == 0)
    return 0;

  return a * power(a, n - 1);
}

unsigned int power_fancy(int a, int n)
{
  int result;

  if (n == 0)
    return 1;

  if (a == 0)
    return 0;

  result = power_fancy(a, n / 2);
  return result * result * (((n % 2) == 0) ? 1 : a);
}

int sumDigit(int n)
{
  if (n == 0)
    return 0;

  return (n % 10) + sumDigit(n / 10);
}

int binary_search_recursive(int *array, int lo, int hi, int key)
{
  int mid;

  if (array == NULL)
    return 0;

  if (lo > hi)
    return 0;

  mid = lo + (hi - lo) / 2;

  if (key < array[mid])
    return binary_search_recursive(array, lo, mid - 1, key);
  else if (key > array[mid])
    return binary_search_recursive(array, mid + 1, hi, key);
  else
    return 1;
}

int isPalidromeHelper(char *str, int lo, int hi)
{
  // case for even or odd length cases
  if (lo >= hi)
    return 1;
  else if (str[lo] != str[hi])
    return 0;
  else
    return isPalidromeHelper(str, lo + 1, hi - 1);
}

int isPalidrome(char *str, int n)
{
  if (str == NULL || n == 0)
    return 0;

  return isPalidromeHelper(str, 0, n - 1);
}

int main(int argc, char **argv)
{
	int a = 2, b = 5;
  int array[] = {13, 27, 78, 42, 68, 2, 1729, 5, 21, 5, 5, 47, 14};

	printf("%d! = %d\n\n", b, factorial(b));

	printf("%d * %d = %d\n", a, b, mult(a, b));
	printf("%d ^ %d = %d\n", a, b, power(a, b));
	printf("%d ^ %d = %d\n\n", a, b, power_fancy(a, b));

	print_string("sandwiches", strlen("sandwiches"));
	print_string_fancy("sandwiches");
  print_string_alternative("sandwiches", strlen("sandwiches"));
  printf("\n");
  print_string_reverse_fancy("sandwiches", strlen("sandwiches"), strlen("sandwiches"));
	print_string_reverse("sandwiches", strlen("sandwiches"));


  printf("sum(5) = %d\n\n", sum(5));

  printf("Max element in array: %d\n", find_max_array(array, 13));
  printf("Max element in array: %d\n", find_max_array_fancy(array, 13));
  printf("Max element in array: %d\n\n", find_max_array_super_fancy(array, 13));

  printf("factorial(4) = %d\n\n", factorial(4));

  printf("Min element in array: %d\n", find_min_array(array, 13));
  printf("Min element in array: %d\n", find_min_array_fancy(array, 13));
  printf("Min element in array: %d\n\n", find_min_array_super_fancy(array, 13));

	return 0;
}
