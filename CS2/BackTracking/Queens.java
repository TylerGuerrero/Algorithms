
// Anatomy of a Back Tracking Solution

// 1) Base Case
// 2) (Optional) check for duplicate state
// 3) Generate Possible move
// 3a) Check validity of move
// 3b) Change state
// 3c) Perform Recursive Descent
// 3d) (Optional) Process return call
// 3e) (Optional) Undo state change


import java.io.*;
import java.util.*;

public class Queens
{

  public static int nQueens(int n)
  {
    boolean [] used_rows = new boolean[n];
    boolean [] used_mdiag = new boolean[2 * n];
    boolean [] used_cdiag = new boolean[2 * n];
    int [] whichRowHasQueen = new int[n];
    return nQueens(n, used_rows, used_mdiag, used_cdiag, whichRowHasQueen, 0);
  }

  private static int nQueens(int n, boolean [] used_rows, boolean [] used_mdiag, boolean [] used_cdiag, int [] whichRowHasQueen, int col)
  {
    // base case
    if (col == n)
    {
      printSolution(whichRowHasQueen);
      return 1;
    }

    int count = 0;
    for (int row = 0; row < n; row++)
    {
      // Generate moves
      int md = col + row;
      int cd = (col - row) + (n - 1);

      // check validity of move
      if (!used_rows[row] && !used_mdiag[md] && !used_cdiag[cd])
      {
        // change state
        used_rows[row] = used_cdiag[cd] = used_mdiag[md] = true;
        whichRowHasQueen[col] = row;

        // perform Recursive Descent and process recursive return call
        count += nQueens(n, used_rows, used_mdiag, used_cdiag, whichRowHasQueen, col + 1);

        // undo state change
        used_rows[row] = used_cdiag[cd] = used_mdiag[md] = false;
      }
    }

    return count;
  }

  public static void printSolution(int [] whichRowHasQueen)
  {
    int len = whichRowHasQueen.length;

    for (int row = 0; row < len; row++)
    {
      for (int col = 0; col < len; col++)
      {
        System.out.print((whichRowHasQueen[col] == row) ? "Q" : ".");
      }
      System.out.println();
    }
    System.out.println();

  }

  public static void main(String [] args)
  {
    // If we have a command line argument, use that as 'n'. Otherwise,
    // default to n = 4.
    int n = (args.length < 1) ? 4 : Integer.parseInt(args[0]);
    int result = nQueens(n);
    System.out.println("Number of solutions for " + n + "-queens problem: " + result);
  }
}
