// 1) -if we have a negative cycle cannot run dijkstra or bellman ford algorithm
//    -if we were to redefine the def of cycle to include repeated edges every edge with a negative edge will be a negative cycle

// 2) if we have a negative weight edge we cannot run dijksta algorithm on it it wil produce the wrong result
//    if we have a negative wieghted edge we can run bellmanford algorithm

// 3) - if we have a undirected graph that has negative edges -- (Can't use BellmanFord or Dijksta)
//    - if we have a undirected graph with postitve edges -- (Can use Dijksta and Bellman Ford)
//    - if we have a directed graph with negative edges -- (Can only use Bellmand Ford)
//    - if we have a directed graph with postitve edges -- (Can use Dijsktra and Bellmand Ford)

// 4) Adj matrix: Dijsktra: O(|V|^2 log|V|), Bellmand ford: O(|V|^3)

// at the 1st iteration of the outer loop from the source all vertices that have 1 edge from the source will be updated
// at the 2st iteration of the outer loop from the source all vertices that have 2 edge from the source will be updated
// at the 3rd iteration of the outer loop from the source all vertices that have 3 edge from the source will be updated
// and so on .... notice to the longest path you can take from source to some vertice will go through every vertice exaclty once so its V - 1 edges

import java.io.*;
import java.util.*;

public class BellmanFord
{
  private int [][] matrix;
  private int V;
  private static final int oo = (int)(1e9);

  BellmanFord(String filename) throws IOException
  {
    Scanner in = new Scanner(new File(filename));

    V = in.nextInt();
    matrix = new int[V][V];

    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        matrix[i][j] = in.nextInt();
  }

  // Big-O: O(|V|^3), Space-Complexity: O(|V|)
  public void bellmanFordOne(int source)
  {
    int [] dist = new int[matrix.length];
    Arrays.fill(dist, oo);
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++)
    {
      for (int j = 0; j < V; j++)
      {
        for (int k = 0; k < V; k++)
        {
          if (matrix[j][k] != 0)
          {
            if (dist[j] + matrix[j][k] < dist[k])
              dist[k] = dist[j] + matrix[j][k];
          }
        }
      }
    }

    // Check for negative cycle
    for (int i = 0; i < matrix.length; i++)
    {
      for (int j = 0; j < matrix.length; i++)
      {
        if (matrix[i][j] != 0)
        {
          if (dist[i] + matrix[i][j] < dist[j])
          {
            System.out.println("Negative Cycle Exists !!!");
          }
        }
      }
    }
  }

  // Big-O: O(|V|^3), Space-Complexity: O(|V|)
  public void bellmanFordTwo(int source)
  {
    int [] dist = new int[matrix.length];
    Arrays.fill(dist, oo);
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++)
    {
      boolean keepGoing = false;
      for (int j = 0; j < matrix.length; j++)
      {
        for (int k = 0; k < matrix.length; k++)
        {
          if (matrix[j][k] != 0)
          {
            if (dist[j] + matrix[j][k] < dist[k])
            {
              dist[k] = dist[j] + matrix[j][k];
              keepGoing = true;
            }
          }
        }
      }

      if (!keepGoing)
        break;
    }

    // Check for negative cycles
    for (int i = 0; i < matrix.length; i++)
    {
      for (int j = 0; j < matrix.length; j++)
      {
        if (matrix[i][j] != 0)
        {
          if (dist[i] + matrix[i][j] < dist[j])
          {
            System.out.println("Negative Cycle Exists !!!");
          }
        }
      }
    }
  }

  // Big-O: O(|V|^3), Space-Complexity: O(|V|)
  public void bellmanFordThree(int source)
  {
    int [] dist = new int[matrix.length];
    Arrays.fill(dist, oo);
    dist[source] = 0;

    boolean keepGoing = false;
    for (int i = 0; i < V; i++)
    {
      keepGoing = false;
      for (int j = 0; j < V; j++)
      {
        for (int k = 0; k < V; k++)
        {
          if (matrix[j][k] != 0)
          {
            if (dist[j] + matrix[j][k] < dist[k])
            {
              dist[k] = dist[j] + matrix[j][k];
              keepGoing = true;
            }
          }
        }
      }

      if (!keepGoing)
        break;
    }

    if (keepGoing)
      System.out.println("Negative Cycle Exists !!!");  
  }
}
