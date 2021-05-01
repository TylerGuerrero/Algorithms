// Hamilton.java
// =============
// This program reads a graph from a file (in 0-1 matrix format) and determines
// whether it has a Hamiltonian cycle. The solution uses backtracking. It
// attempts to form a path that uses every node in the graph. If it succeeds,
// it checks whether there is an edge from the last node in that path to the
// first node -- thus completing the cycle. If not, or if the algorithm reaches
// a dead end and cannot add any new nodes to the path it's constructing, it
// returns to the previous call and looks for other possible paths (i.e., it
// backtracks to the last decision point).

// Anatomy of a BackTracking solution
// 1) Base Case
// 2) (Optional) Check for duplicate state
// 3) Generate Possible Move
// 3a) Check fort validity of move
// 3b) Change state
// 3c) Perform recsurive descent
// 3d) Process recusrive return call
// 3e) Undo state change

import java.io.*;
import java.util.*;

public class Hamiltonian
{
  private boolean [][] matrix;
  private int N;

  Hamiltonian(String filename) throws IOException
  {
    Scanner in = new Scanner(new File(filename));

    N = in.nextInt();
    matrix = new boolean[N][N];

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        matrix[i][j] = (in.nextInt() == 1);
  }

  public boolean hasHamiltonianCycle()
  {
    // track and insert the verticies of the path of the Hamiltonian cycle
    int [] path = new int[matrix.length];

    // track which vertices we have been to in the graph
    boolean [] visited = new boolean[matrix.length];

    path[0] = 0;
    visited[0] = true;

    if (hasHamiltonianCycle(path, visited, 1))
    {
      for (int i = 0; i < matrix.length; i++)
        System.out.print(((char)(path[i] + 'A')) + " ");

      System.out.print(((char)(path[0] + 'A')) + " ");
      return true;
    }

    return false;
  }

  private boolean hasHamiltonianCycle(int [] path, boolean [] visited, int k)
  {
    int v = path[k - 1];

    if (k == matrix.length)
      return matrix[v][path[0]];

    for (int i = 0; i < matrix.length; i++)
    {
      if (matrix[v][i] && !visited[i])
      {
        path[k] = i;
        visited[i] = true;

        if (hasHamiltonianCycle(path, visited, k + 1))
          return true;

        visited[i] = true;
      }
    }

    return false;
  }

  public boolean hasHamiltonianPath()
  {
    // track and insert the verticies of the path of the Hamiltonian cycle
    int [] path = new int[matrix.length];

    // track which vertices we have been to in the graph
    boolean [] visited = new boolean[matrix.length];

    path[0] = 0;
    visited[0] = true;

    if (hasHamiltonianPath(path, visited, 1))
    {
      for (int i = 0; i < matrix.length; i++)
        System.out.print(((char)(path[i] + 'A')) + " ");
      return true;
    }

    return false;
  }

  private boolean hasHamiltonianPath(int [] path, boolean [] visited, int k)
  {
    int v = path[k - 1];

    if (k == matrix.length)
      return true;

    for (int i = 0; i < matrix.length; i++)
    {
      if (matrix[v][i] && !visited[i])
      {
        path[k] = i;
        visited[i] = true;

        if (hasHamiltonianPath(path, visited, k + 1))
          return true;

        visited[i] = false;
      }
    }

    return false;
  }

	public static void main(String [] args) throws IOException
	{
		if (args.length < 1)
		{
			System.out.println("Proper syntax: java Hamilton <filename>");
			return;
		}

		// The name of the file to open is supplied as a command line argument.
		Hamiltonian g = new Hamiltonian(args[0]);
		System.out.println(g.hasHamiltonianCycle());
    System.out.println(g.hasHamiltonianPath());
	}
}
