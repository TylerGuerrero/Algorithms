import java.io.*;
import java.util.*;
import java.awt.*;

// DP Solution
// 1) A combo of exhaustive search and greedy approach
// 2) Will store the sub problems in a dp array
// 3) The dp solution will have strong fidelity to the recurrence relation
// 4) The dimensions of the dp array will correlate to the input

public class Binomial
{
  private static final int UNINITIALIZED = -1;

  // (n, k) = (row, col)

  // Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space-Complxity: O(n)
  public static int binomial(int n, int k)
  {
    if (k == 0 || k == n)
      return 1;

    return binomial(n - 1, k - 1) + binomial(n - 1, k);
  }

  // Big-O: Worst-Case: O(nk), Best-Case: O(nk), Space-Complxity: O(nk)
  public static int binomialMemo(int n, int k)
  {
    int [][] memo = new int[n + 1][k + 1];

    for (int i = 0; i <= n; i++)
      Arrays.fill(memo[i], UNINITIALIZED);

    return binomialMemo(n, k, memo);
  }

  // Big-O: Worst-Case: O(nk), Best-Case: O(nk), Space-Complxity: O(nk)
  private static int binomialMemo(int n, int k, int [][] memo)
  {
    // base case
    if (k == 0 || k == n)
      return 1;

    // extra flavor of a base case
    if (memo[n][k] != UNINITIALIZED)
      return memo[n][k];

    memo[n][k] = binomialMemo(n - 1, k - 1, memo) + binomialMemo(n - 1, k, memo);
    return memo[n][k];
  }

  public static int binomialMemoUltra(int n, int k)
  {
    HashMap<Point, Integer> memo = new HashMap<Point, Integer>();
    return binomialMemoUltra(n, k, memo);
  }

  private static int binomialMemoUltra(int n, int k, HashMap<Point, Integer> memo)
  {
    // base case
    if (k == 0 || k == n)
      return 1;

    // extra flavor of a base case
    Integer memoized = memo.get(new Point(n, k));
    if (memoized != null)
      return memoized;

    int result = binomialMemoUltra(n - 1, k - 1, memo) + binomialMemoUltra(n - 1, k, memo);
    memo.put(new Point(n, k), result);
    return result;
  }

  // Big-O: Worst-Case: O(nk), Best-Case: O(nk), Space-Complxity: O(nk)
  public static int binomialDP(int n, int k)
  {
    int [][] dp = new int[n + 1][k + 1];

    // pre-processing bases cases
    // binomial(n, 0)
    for (int i = 0; i <= n; i++)
      dp[i][0] = 1;

    // binomial(n, n)
    for (int i = 0; i <= k; i++)
      dp[i][i] = 1;

    for (int row = 2; row <= n; row++)
      for (int col = 1; col <= Math.min(row - 1, k); col++)
        dp[row][col] = dp[row - 1][col - 1] + dp[row - 1][col];

    return dp[n][k];
  }

  public static void main(String [] args)
  {
    if (args.length < 2)
    {
      System.err.println("Proper syntax: java Binomial <n> <k>");
      return;
    }

    int n = Integer.parseInt(args[0]);
    int k = Integer.parseInt(args[1]);
    System.out.println("C(" + n + ", " + k + ") = " + binomialMemo(n, k));
    System.out.println("C(" + n + ", " + k + ") = " + binomialMemoUltra(n, k));
    System.out.println("C(" + n + ", " + k + ") = " + binomialDP(n, k));
    System.out.println("C(" + n + ", " + k + ") = " + binomial(n, k));
  }
}
