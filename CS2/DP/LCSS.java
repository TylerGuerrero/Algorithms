import java.io.*;
import java.util.*;

// Anatomy of a DP Solution
// 1) Combo of exhaustive search and greedy algo
// 2) Will store the subprobelms of each computation into your dp array
// 3) The DP solution has strong fidelity to the recurence relation
// 4) The inputs to our funtion will stringly correlate to the dimensions to the dp array

// Anatamy of a Memo Solution
// 1) base case
// 2) extra flavor of a base case
// 3) store result in memo array or hashmap
// 4) return result

import java.io.*;
import java.util.*;

public class LCSS
{
  private static final int UNINITIALIZED = -1;

  // 1) Have to find the longest subsequence between two strings
  // 2) The subsequence has to be in order but not contiguous

  // recursive solution that includes empty strings

  // Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space-Complexity: O(n)
  public static int lcss(String a, String b)
  {
    if (a.length() == 0 || b.length() == 0)
      return 0;

    String asub = a.substring(0, a.length() - 1);
    String bsub = b.substring(0, b.length() - 1);

    if (a.charAt(a.length() - 1) == b.charAt(b.length() - 1))
      return 1 + lcss(asub, bsub);

    return Math.max(lcss(asub, b), lcss(a, bsub));
  }

  // recursive memo solution that includes empty strings

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(nm)
  public static int lcssMemo(String a, String b)
  {
    // empty string included
    int [][] memo = new int[a.length() + 1][b.length() + 1];
    for (int i = 0; i <= a.length(); i++)
      Arrays.fill(memo[i], UNINITIALIZED);

    return lcssMemo(a, b, memo);
  }

  // recursive memo solution that includes empty strings

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(n)
  private static int lcssMemo(String a, String b, int [][] memo)
  {
    // base case
    if (a.length() == 0 || b.length() == 0)
      return 0;

    // extra flavor of a base case
    if (memo[a.length()][b.length()] != UNINITIALIZED)
      return memo[a.length()][b.length()];

    String asub = a.substring(0, a.length() - 1);
    String bsub = b.substring(0, b.length() - 1);

    if (a.charAt(a.length() - 1) == b.charAt(b.length() - 1))
      memo[a.length()][b.length()] = 1 + lcssMemo(asub, bsub);
    else
      memo[a.length()][b.length()] = Math.max(lcssMemo(asub, b),
                                            lcssMemo(a, bsub));

    return memo[a.length()][b.length()];
  }

  // dp solution that includes empty strings

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(nm)
  public static int lcssDP(String a, String b)
  {
    // empty string included
    int [][] dp = new int[a.length() + 1][b.length() + 1];

    // preprocessing base cases

    // when empty string gets compared to first char of string a
    for (int i = 0; i <= a.length(); i++)
      dp[i][0] = 0;

    // when empty string gets compared to first char of string b
    for (int i = 0; i <= b.length(); i++)
      dp[0][i] = 0;

    for (int i = 1; i <= a.length(); i++)
      for (int j = 1; j <= b.length(); j++)
        if (a.charAt(i - 1) == b.charAt(j - 1))
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);

    return dp[a.length()][b.length()];
  }

  // recursive solution that does not include empty strings

  // Big-O: Worst-Case: O(2^n), Best-Case: O(2^n), Space-Complexity: O(n)
  public static int lcssRecursiveNoEmptyStrings(String a, String b)
  {
    // one char at string a
    if (a.length() == 1)
      return b.indexOf(a.charAt(0)) > 0 ? 1 : 0;

    if (b.length() == 1)
      return a.indexOf(b.charAt(0)) > 0 ? 1 : 0;

      String asub = a.substring(0, a.length() - 1);
      String bsub = b.substring(0, b.length() - 1);

    if (a.charAt(a.length() - 1) == b.charAt(b.length() - 1))
      return 1 + lcssRecursiveNoEmptyStrings(asub, bsub);

    return Math.max(lcssRecursiveNoEmptyStrings(a, bsub),
                    lcssRecursiveNoEmptyStrings(asub, b));
  }

  // dp solution that does not include empty strings

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(nm)
  public static int lcssDPNoEmptyStrings(String a, String b)
  {
    // empty string not included
    int [][] dp = new int[a.length()][b.length()];
    int i, j;
    // preprocessing base cases

    // compare char a.charAt(0) to all of string b
    for (i = 0; i < b.length() && a.charAt(0) != b.charAt(i); i++)
      dp[0][i] = 0;
    for (i = i; i < b.length(); i++)
      dp[0][i] = 1;

    // compare char b.charAt(0) to all of string a
    for (i = 0; i < a.length() && b.charAt(0) != a.charAt(i); i++)
        dp[i][0] = 0;
    for (i = i; i < a.length(); i++)
      dp[i][0] = 1;

    for (i = 1; i < a.length(); i++)
      for (j = 1; j < b.length(); j++)
        if (a.charAt(i) == b.charAt(j))
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);

    return dp[a.length() - 1][b.length() - 1];
  }

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(m)
  public static int lcssDPLessSpace(String a, String b)
  {
    // empty string included
    int [][] dp = new int[2][b.length() + 1];

    // pre-processing
    // Assumes first row and column are already zeroed out.

    for (int i = 1; i <= a.length(); i++)
      for (int j = 1; j <= b.length(); j++)
        if (a.charAt(i - 1) == b.charAt(j - 1))
          dp[i % 2][j] = 1 + dp[(i - 1) % 2][j - 1];
        else
          dp[i % 2][j] = Math.max(dp[(i - 1) % 2][j],
                                  dp[i % 2][j - 1]);

    return dp[a.length() % 2][b.length()];
  }

  // Big-O: Worst-Case: O(nm), Best-Case: O(nm), Space-Complexity: O(MIN(n,m))
  public static int lcssDPEvenLessSpace(String a, String b)
  {
    if (a.length() < b.length())
    {
      String temp = a; a = b; b = temp;
    }

    // empty string included
    int [][] dp = new int[2][b.length() + 1];

    // preprossesing bases cases
    // Assumes first row and column are already zeroed out.

    for (int i = 1; i <= a.length(); i++)
      for (int j = 1; j <= b.length(); j++)
        if (a.charAt(i - 1) == b.charAt(j - 1))
          dp[i % 2][j] = 1 + dp[(i - 1) % 2][j - 1];
        else
          dp[i % 2][j] = Math.max(dp[(i - 1) % 2][j],
                                  dp[i % 2][j - 1]);

    return dp[a.length() % 2][b.length()];
  }

  public static void main(String [] args)
  {
    System.out.println(lcss("goodmorning", "hodor"));    // odor => 4
    System.out.println(lcss("hodor", "goodmorning"));    // odor => 4
    System.out.println(lcss("hodorx", "goodmorningx"));  // odorx => 5
    System.out.println(lcss("racecar", "cream"));        // rea => 3
    System.out.println(lcss("modohodo", "hodo"));        // hodo => 4
    System.out.println(lcss("kitten", "smithing"));      // itn => 3

    System.out.println();

    System.out.println(lcssMemo("goodmorning", "hodor"));    // odor => 4
    System.out.println(lcssMemo("hodor", "goodmorning"));    // odor => 4
    System.out.println(lcssMemo("hodorx", "goodmorningx"));  // odorx => 5
    System.out.println(lcssMemo("racecar", "cream"));        // rea => 3
    System.out.println(lcssMemo("modohodo", "hodo"));        // hodo => 4
    System.out.println(lcssMemo("kitten", "smithing"));      // itn => 3

    System.out.println();

    System.out.println(lcssDP("goodmorning", "hodor"));    // odor => 4
    System.out.println(lcssDP("hodor", "goodmorning"));    // odor => 4
    System.out.println(lcssDP("hodorx", "goodmorningx"));  // odorx => 5
    System.out.println(lcssDP("racecar", "cream"));        // rea => 3
    System.out.println(lcssDP("modohodo", "hodo"));        // hodo => 4
    System.out.println(lcssDP("kitten", "smithing"));      // itn => 3

    System.out.println();


		System.out.println(lcssRecursiveNoEmptyStrings("goodmorning", "hodor"));    // odor => 4
		System.out.println(lcssRecursiveNoEmptyStrings("hodor", "goodmorning"));    // odor => 4
		System.out.println(lcssRecursiveNoEmptyStrings("hodorx", "goodmorningx"));  // odorx => 5
		System.out.println(lcssRecursiveNoEmptyStrings("racecar", "cream"));        // rea => 3
		System.out.println(lcssRecursiveNoEmptyStrings("modohodo", "hodo"));        // hodo => 4
		System.out.println(lcssRecursiveNoEmptyStrings("kitten", "smithing"));      // itn => 3

		System.out.println();

    System.out.println(lcssDPNoEmptyStrings("goodmorning", "hodor"));    // odor => 4
    System.out.println(lcssDPNoEmptyStrings("hodor", "goodmorning"));    // odor => 4
    System.out.println(lcssDPNoEmptyStrings("hodorx", "goodmorningx"));  // odorx => 5
    System.out.println(lcssDPNoEmptyStrings("racecar", "cream"));        // rea => 3
    System.out.println(lcssDPNoEmptyStrings("modohodo", "hodo"));        // hodo => 4
    System.out.println(lcssDPNoEmptyStrings("kitten", "smithing"));      // itn => 3

    System.out.println();

    System.out.println(lcssDPLessSpace("goodmorning", "hodor"));    // odor => 4
    System.out.println(lcssDPLessSpace("hodor", "goodmorning"));    // odor => 4
    System.out.println(lcssDPLessSpace("hodorx", "goodmorningx"));  // odorx => 5
    System.out.println(lcssDPLessSpace("racecar", "cream"));        // rea => 3
    System.out.println(lcssDPLessSpace("modohodo", "hodo"));        // hodo => 4
    System.out.println(lcssDPLessSpace("kitten", "smithing"));      // itn => 3

    System.out.println();

		System.out.println(lcssDPEvenLessSpace("goodmorning", "hodor"));    // odor => 4
		System.out.println(lcssDPEvenLessSpace("hodor", "goodmorning"));    // odor => 4
		System.out.println(lcssDPEvenLessSpace("hodorx", "goodmorningx"));  // odorx => 5
		System.out.println(lcssDPEvenLessSpace("racecar", "cream"));        // rea => 3
		System.out.println(lcssDPEvenLessSpace("modohodo", "hodo"));        // hodo => 4
		System.out.println(lcssDPEvenLessSpace("kitten", "smithing"));      // itn => 3

		System.out.println();
  }
}
