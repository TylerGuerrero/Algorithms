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

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static int keyCounter(int [] array, int key)
  {
    int cnt = 0;
    for (int i = 0; i < array.length; i++)
      if (array[i] == key)
        cnt++;

    return cnt;
  }

  // Big-O: Worst-Case: O(logn + n), Best-Case: O(logn), Space Complexity: O(1)
  public static int keyCounterFancy(int [] array, int key)
  {
    int lo, cnt;
    int hi = array.length - 1;
    lo = cnt = 0;

    while (lo <= hi)
    {
      int mid = lo + (hi - lo) / 2;

      if (key < array[mid])
        hi = mid - 1;
      else if (key > array[mid])
        lo = mid + 1;
      else
      {
        int left = mid - 1;
        while (left >= 0 && array[left] == key)
        {
          left--;
          cnt++;
        }

        int right = mid;
        while (right < array.length && array[right] == key)
        {
          right++;
          cnt++;
        }

        return cnt;
      }
    }

    return 0;
  }

  // Big-O: Worst-Case: O(logn), Best-Case: O(logn), Space Complexity: O(1)
  // (rightCall) - (leftCall) + 1
  public static int keyCounterFanciest(int [] array, int key, boolean leftMost)
  {
    int lo = 0;
    int hi = array.length - 1;
    int idx = -1;

    while (lo <= hi)
    {
      int mid = lo + (hi - lo) / 2;

      if (key < array[mid])
        hi = mid - 1;
      else if (key > array[mid])
        lo = mid + 1;
      else
      {
        idx = mid;

        if (leftMost)
          hi = mid - 1;
        else
          lo = mid + 1;
      }
    }

    return idx;
  }

  // Big-O: Worst-Case: O(n^2), Best-Case: O(1), Space Complexity: O(1)
  public static boolean canMakeSum(int [] array, int target)
  {
    for (int i = 0; i < array.length; i++)
      for (int j = i + 1; j < array.length; j++)
        if (array[i] + array[j] == target)
          return true;

    return false;
  }

  // Big-O: Worst-Case: O(nlogn), Best-Case: O(1), Space Complexity: O(1)
  public static boolean canMakeSumFancy(int [] array, int target)
  {
    for (int i = 0; i < array.length; i++)
      if (Arrays.binarySearch(array, target - array[i]) >= 0)
        return true;

    return false;
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(1), Space Complexity: O(1)
  public static boolean canMakeSumFanciest(int [] array, int target)
  {
    int lo = 0;
    int hi = array.length - 1;

    while (lo <= hi)
    {
      int sum = array[lo] + array[hi];

      if (sum < target)
        lo++;
      else if (sum > target)
        hi--;
      else
        return true;
    }

    return false;
  }

  // Big-O: Worst-Case: O(n^2), Best-Case: O(n^2), Space Complexity: O(1)
  public static int mcss(int [] array)
  {
    int max = 0;
    for (int i = 0; i < array.length; i++)
    {
      int sum = 0;
      for(int j = i; j < array.length; j++)
      {
        sum += array[j];

        if (sum > max)
          max = sum;
      }
    }

    return max;
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  public static int mcssOptimized(int [] array)
  {
    int max = 0;
    int sum = 0;

    for (int i = 0; i < array.length; i++)
    {
      sum += array[i];

      if (sum > max)
        max = sum;
      else if (sum < 0)
        sum = 0;
    }

    return max;
  }
}
