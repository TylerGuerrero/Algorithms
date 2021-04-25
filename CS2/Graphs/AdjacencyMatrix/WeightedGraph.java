import java.util.*;
import java.io.*;

class Vertex implements Comparable<Vertex>
{
  int id, dist;

  Vertex(int id, int dist)
  {
    this.id = id;
    this.dist = dist;
  }

  public int compareTo(Vertex v)
  {
    return this.dist - v.dist;
  }

  public String toString()
  {
    return "Shortest Cost of vertex at " + (char)(this.id + 'A') + ": " + this.dist;
  }
}

public class WeightedGraph
{
  private int [][] matrix;
  private int N;
  private static final int oo = (int)(1e9);

  WeightedGraph(String filename) throws IOException
  {
    Scanner in = new Scanner(new File(filename));

    N = in.nextInt();
    matrix = new int[N][N];

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        matrix[i][j] = in.nextInt();
  }

  // Big-O: O(|V|^2 log|V|^2)
  public void runDijkstra(int source)
  {
    boolean [] visited = new boolean[matrix.length];
    int [] dist = new int[matrix.length];
    PriorityQueue<Vertex> minheap = new PriorityQueue<Vertex>();
    int numVisited = 0;

    Arrays.fill(dist, oo);
    dist[source] = 0;

    // stores index and value of the dist element
    for (int i = 0; i < matrix.length; i++)
      minheap.add(new Vertex(i, dist[i]));

    while (!minheap.isEmpty() && numVisited < N)
    {
      // Get the minimum dist value and index
      Vertex v = minheap.remove();

      if (visited[v.id]) continue;

      // visited and dist index's are in unnison to each other
      visited[v.id] = true;
      numVisited++;
      System.out.println(v);

      for (int i = 0; i < matrix.length; i++)
      {
        if ((matrix[v.id][i] > 0) && (!visited[i]) && (dist[v.id] + matrix[v.id][i] < dist[i]))
        {
          // Once each vertex has been visited, we'll just stop coming into
          // the while-loop, and all those duplicates will be ignored.
          // The index i will have been put in twice with different dist[i]
          // vals so it will be popped but will have been visited before so
          // it will be ignored
          dist[i] = dist[v.id] + matrix[v.id][i];
          minheap.add(new Vertex(i, dist[i]));
        }
      }
    }

    if (numVisited != matrix.length)
      System.out.println("Disconnected Graph exist !!!... Yikes");
  }

  public static void main(String [] args) throws IOException
  {
    WeightedGraph g = new WeightedGraph("dijkstra-graph.txt");
		g.runDijkstra(0);
  }
}
