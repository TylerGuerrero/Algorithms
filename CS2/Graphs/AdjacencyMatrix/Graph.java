// Graph.java
// ==========
// This is a framework for initializing a graph from an input file that contains
// an adjacency matrix. The first line of the input file indicates how many
// vertices are in the graph. The following n lines contain the adjacency matrix
// for the (zeros and ones). For example:

//    4
//    0 1 0 1
//    1 0 1 1
//    0 1 0 1
//    1 1 1 0

// ...which corresponds to the unweighted, undirected graph:
//    0---1
//     \ /|
//      X |
//     / \|
//    2---3

// These values are read into a boolean matrix, and we perform breadth-first and
// depth-first search traversals starting from an arbitrary vertex.

import java.io.*;
import java.util.*;

public class Graph
{
  private boolean [][] matrix;
  private int N;

  Graph(String filename) throws IOException
  {
    Scanner in = new Scanner(new File(filename));

    N = in.nextInt();
    matrix = new boolean[N][N];

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        matrix[i][j] = (in.nextInt() == 1);
  }

  // Iterative BFS places vertices in a queue. When we pull a vertex out of
  // the queue, we process it (in this case, print it to the screen), then
  // place all its unvisited neighbors in the queue. We mark each vertex as
  // visited as it goes into the queue, because that ensures we never place
  // a vertex into the queue more than once. (That can significantly reduce
  // the space complexity of this algorithm when dealing with a large, dense
  // graph.)

  // Iterative BFS method.
  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  public void BFS(int source)
  {
    boolean [] visited = new boolean[matrix.length];
    Queue<Integer> q = new LinkedList<Integer>();

    visited[source] = true;
    q.add(source);

    while (!q.isEmpty())
    {
      int node = q.remove();
      System.out.println(node);

      for (int i = 0; i < matrix.length; i++)
        if (matrix[node][i] && !visited[i])
        {
          visited[i] = true;
          q.add(i);
        }
    }
  }

  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  // Wrapper to our recursive DFS method.
  public void DFS(int source)
  {
    boolean [] visited = new boolean[matrix.length];
    DFS(visited, source);
  }

  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  private void DFS(boolean [] visited, int node)
  {
    visited[node] = true;
    System.out.println(node);

    for (int i = 0; i < matrix.length; i++)
      if (matrix[node][i] && !visited[i])
        DFS(visited, i);
  }

  // Iterative BFS method.
  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  public void DFSIterative(int source)
  {
    Stack<Integer> s = new Stack<Integer>();
    boolean [] visited = new boolean[matrix.length];

    s.push(source);

    while (!s.isEmpty())
    {
      int node = s.pop();

      // Stack may have same vertex twice
      if (visited[node]) continue;

      visited[node] = true;
      System.out.println(node);

      for (int i = 0; i < matrix.length; i++)
        if (matrix[node][i] && !visited[i])
          s.push(i);
    }
  }

  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  public int countConnectedComponent()
  {
    boolean [] visited = new boolean[matrix.length];
    int cnt = 0;

    for (int i = 0; i < matrix.length; i++)
    {
      if (!visited[i])
      {
        DFS(visited, i);
        cnt++;
      }
    }

    return cnt;
  }

  // Big-O: O(|V|^2), Space-Complexity: O(|V|)
  public void topoSort()
  {
    int [] incoming = new int[matrix.length];
    Queue<Integer> q = new ArrayDeque<Integer>();
    int cnt = 0;

    // Count the number of incoming edges incident to each vertex.
    for (int i = 0; i < matrix.length; i++)
      for (int j = 0; j < matrix.length; j++)
        incoming[j] += ((matrix[i][j]) ? 1 : 0);

    // Any vertex with zero incoming edges is ready to be visited, so add it to
  	// the queue.
    for (int i = 0; i < matrix.length; i++)
      if (incoming[i] == 0)
        q.add(i);

    while (!q.isEmpty())
    {
      // Pull a vertex out of the queue and add it to the topological sort.
      // The vertex will have 0 incoming edges
      int node = q.remove();
      System.out.println(node);

      // Count the number of unique vertices we see.
      cnt++;

      // All vertices we can reach via an edge from the current vertex should
      // have their incoming edge counts decremented. If one of these hits
      // zero, add it to the queue.
      for (int i = 0; i < matrix.length; i++)
        if (matrix[node][i] && --incoming[i] == 0)
          q.add(i);
    }

    if (cnt != matrix.length)
      System.out.println("A cycle exist");
  }

  public static void main(String [] args) throws Exception
  {
  	Graph g = new Graph("g1.txt");
  	System.out.println("BFS(0):"); g.BFS(0);
  	System.out.println("DFSIterative(3):"); g.DFSIterative(3);
  	System.out.println("DFS(3):"); g.DFS(3);
    System.out.println("countConnectedCoponents(): " + g.countConnectedComponent());
  }
}
