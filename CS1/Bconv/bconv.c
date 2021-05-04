#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g'};

// base 10 -> base n

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
void fromBase10Helper(int n, int base)
{
  if (n == 0)
    return;

  fromBase10Helper(n / base, base);
  printf("%c", digits[n % base]);
}

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
void fromBase10(int n, int base)
{
  if (n == 0)
    printf("0\n");
  else
  {
    fromBase10Helper(n, base);
    printf("\n");
  }
}

void panic(char *err_msg)
{
	fprintf(stderr, "%s\n", err_msg);
	exit(1);
}

int toDigit(char ch)
{
  char err_msg[100];
  ch = tolower(ch);

  if (ch >= '0' && ch <= '9')
    return ch - '0';
  else if (ch >= 'a' && ch <= 'z')
    return ch - 'a' + 10;
  else
  {
    sprintf(err_msg, "Fatality in toDigit(): Could not convert '%c' to int!", ch);
    panic(err_msg);
  }
}

// base n -> base 10

// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
int toBase10(char *str, int base)
{
  int i, len, result = 0;

  if (str == NULL)
    return INT_MIN;

  len = strlen(str);

  for (i = 0; i < len; i++)
  {
    result *= base;
    result += toDigit(str[i]);
  }

  return result;
}


// Example program calls:
//
//   ./a.out a2d 16 10
//   ./a.out 2605 10 16
//   ./a.out 1101011 2 4
int main(int argc, char **argv)
{
	int fromBase, toBase, n;

	if (argc < 4)
	{
		fprintf(stderr, "Proper syntax: %s <n> <fromBase> <toBase>\n", argv[0]);
		return 0;
	}

	fromBase = atoi(argv[2]);
	toBase = atoi(argv[3]);

	if (fromBase == 10)
	{
		// This function prints the result.
		fromBase10(atoi(argv[1]), toBase);
	}
	else if (toBase == 10)
	{
		// The toBase10() function doesn't print the result; it just returns it.
		n = toBase10(argv[1], fromBase);
		printf("%d\n", n);
	}
	else
	{
		// If neither the fromBase nor the toBase are 10, we can use 10 as
		// an intermediary base as we perform the conversion. It's nice that
		// the toBase10() function doesn't print the result, because this way
		// our program doesn't print that intermediary value.
		n = toBase10(argv[1], fromBase);
		fromBase10(n, toBase);
	}
	return 0;
}
