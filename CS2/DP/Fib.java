import java.io.*;
import java.util.*;

// DP intro
// 1) A combo of greedy and exhaustive seach algos
// 2) Will avoid repeated computations by storing the sub problems
// 3) The DP solution will strongly correlate to the reccurence relation
// 4) the inputs will govern the dp array dimensions

public class Fib
{
  // Fib base cases: fib(0) = 0, fib(1) = 1
  // simply add the two previous integers into the sequence
  // Fib sequence: 0, 1, 1, 2, 3, 5, 8 ... etc

  private static final int UNINITIALIZED = -1;

  // Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space Complexity: O(n)
  public static int fib(int n)
  {
    if (n < 2)
      return n;

    return fib(n - 1) + fib(n - 2);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  public static int fibMemo(int n)
  {
    int [] memo = new int[n + 1];
    Arrays.fill(memo, UNINITIALIZED);
    return fibMemo(n, memo);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  private static int fibMemo(int n, int [] memo)
  {
    // base case
    if (n < 2)
      return n;

    // extra flavor of a base case to catch repeated computation
    if (memo[n] != UNINITIALIZED)
      return memo[n];

    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  public static int fibUltraMemo(int n)
  {
    HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
    return fibUltraMemo(n, map);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  private static int fibUltraMemo(int n, HashMap<Integer, Integer> memo)
  {
    // base case
    if (n < 2)
      return n;

    // Extra flavor of a base case to see if we stored a repeated computation
    Integer memoized = memo.get(n);
    if (memoized != null)
      return memoized;

    int result = fibUltraMemo(n - 1, memo) + fibUltraMemo(n - 2, memo);
    memo.put(n, result);
    return result;
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(n)
  public static int fibDP(int n)
  {
    if (n < 2)
      return n;

    int [] dp = new int[n + 1];

    // base-cases
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
      dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space Complexity: O(1)
  private static int fibDPFancy(int n)
  {
    if (n < 2)
      return n;

    int [] dp = new int[2];

    // base cases
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
      dp[i % 2] = dp[1] + dp[0];

    return dp[n % 2];
  }

  public static void main(String [] args)
	{
		if (args.length < 1)
		{
			System.err.println("Proper syntax: java Fibonacci <n>");
			return;
		}

		int n = Integer.parseInt(args[0]);
		System.out.println("F(" + n + ") = " + fibMemo(n));
	  System.out.println("F(" + n + ") = " + fibUltraMemo(n));
		System.out.println("F(" + n + ") = " + fibDP(n));
		System.out.println("F(" + n + ") = " + fibDPFancy(n));
		System.out.println("F(" + n + ") = " + fib(n));
	}
}
