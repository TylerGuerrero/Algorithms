import java.io.*;
import java.util.*;

public class Clever
{
  // base case: fib(0) = 0, fib(1) = 1
  // fib sequence: 0, 1, 1, 2, 3, 5, 8, 13... etc

  // Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space Complexity: O(n)
  public static int fib(int n)
  {
    if (n < 2)
      return n;

    return fib(n - 1) + fib(n - 2);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  public static int fibOptimized(int n)
  {
    int [] array = new int[n + 1];

    array[0] = 0;
    array[1] = 1;

    for (int i = 2; i <= n; i++)
      array[i] = array[i - 1] + array[i - 2];

    return array[n];
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static int fibSuperOptimized(int n)
  {
    int [] array = new int[2];

    array[0] = 0;
    array[1] = 1;

    for (int i = 2; i <= n; i++)
      array[i % 2] = array[0] + array[1];

    return array[n % 2];
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static boolean posCount(int [] array, int k)
  {
    int cnt = 0;
    for (int i = 0; i < array.length; i++)
      if (array[i] > 0)
        cnt++;

    return (cnt >= k);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static boolean posCountOptimized(int [] array, int k)
  {
    int cnt = 0;
    for (int i = array.length - 1; i >= 0 && array[i] > 0; i--)
      cnt++;

    return (cnt >= k);
  }

  // Big-O: Worst-Case: O(1), Best-Case: O(1), Space Complexity: O(1)
  public static boolean posCountSuperOptimized(int [] array, int k)
  {
    if (k > array.length) return false;
    if (k <= 0) return true;

    return ((array[array.length - k] > 0));
  }

  // Big-O: Worst-Case: O(1), Best-Case: O(1), Space Complexity: O(1)
  public static int sum(int n)
  {
    if (n < 0)
      return -1 * sum(-n);

    return ((n * (n - 1)) / 2);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static boolean duplicates(int [] array)
  {
    for (int i = 0; i < array.length - 1; i++)
      if (array[i] == array[i + 1])
        return true;

    return false;
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static int findMax(int [] array)
  {
    int max = array[array.length - 1];

    for (int i = array.length - 2; i >= 0 && max < 0; i--)
      if (array[i] > max)
        max = array[i];

    return max;
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static int findMaxOptimized(int [] array)
  {
    for (int i = array.length - 1; i >= 0; i--)
      if (array[i] > 0)
        return array[i];

    return array[0];
  }
}
