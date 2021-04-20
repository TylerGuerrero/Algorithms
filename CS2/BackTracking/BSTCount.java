import java.io.*;
import java.util.*;

public class BSTCount
{
  // Catalan number = (2n!) / (n!(n + 1)!)
  // this will get the total number for distinc bst's you can create with
  // 1 through n values

  // Big-O: O(n^2), Space-Complexity: O(n)
  // [1, 2, 3, ... n]
  public static int countBST(int n)
  {
    if (n <= 1)
      return 1;

    int sum = 0;
    for (int root = 1; root <= n; root++)
    {
      int lCount = countBST(root - 1);
      int rCount = countBST(n - root);
      sum += lCount * rCount;
    }

    return sum;
  }
}
