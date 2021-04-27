// Implementation of BFS(), DFS(), countConnectedCoponents all in Adjacency List
import java.io.*;
import java.util.*;

public class Graph
{
  private ArrayList<LinkedList<Integer>> adjList = new ArrayList<LinkedList<Integer>>();
  private int V;

  Graph(int V)
  {
    this.V = V;

    for (int i = 0; i < V; i++)
      adjList.add(new LinkedList<Integer>());
  }

  public void addEdge(int vertex, int weight)
  {
    adjList.get(vertex).add(weight);
  }

  // Big-O: O(|V| + |E|), Space-Complexity: O(|V|)
  public void BFS(int source)
  {
    boolean [] visited = new boolean[this.V];
    Queue<Integer> q = new LinkedList<Integer>();

    visited[source] = true;
    q.add(source);

    while (!q.isEmpty())
    {
      int node = q.remove();
      System.out.println(node);

      Iterator<Integer> itr = adjList.get(node).iterator();
      while (itr.hasNext())
      {
        int vertex = itr.next();
        if (!visited[vertex])
        {
          q.add(vertex);
          visited[vertex] = true;
        }
      }
    }
  }

  // Big-O: O(|V| + |E|), Space-Complexity: O(|V|)
  public void DFSIterative(int source)
  {
    boolean [] visited = new boolean[this.V];
    Stack<Integer> s = new Stack<Integer>();

    s.push(source);

    while (!s.isEmpty())
    {
      int node = s.pop();

      // case for two nodes within the stack that have not
      // visited yet but have been visited by other nodes
      if (visited[node]) continue;

      visited[node] = true;
      System.out.println(node);

      Iterator<Integer> itr = adjList.get(node).iterator();
      while (itr.hasNext())
      {
        int vertex = itr.next();

        if (!visited[vertex])
          s.push(vertex);
      }
    }
  }

  public void DFS(int source)
  {
    boolean [] visited = new boolean[this.V];
    DFS(source, visited);
  }

  private void DFS(int node , boolean [] visited)
  {
    visited[node] = true;
    System.out.println(node);

    Iterator<Integer> itr = adjList.get(node).iterator();
    while (itr.hasNext())
    {
      int vertex = itr.next();

      if (!visited[vertex])
        DFS(vertex, visited);
    }
  }

  public int countConnectedComponents()
  {
    boolean [] visited = new boolean[this.V];
    int cnt = 0;

    for (int i = 0; i < this.V; i++)
    {
      if (!visited[i])
      {
        DFS(i, visited);
        cnt++;
      }
    }

    return cnt;
  }

  public static void main(String [] args)
  {
    Graph g = new Graph(4);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    System.out.println("BFS(2):"); g.BFS(2);
  	System.out.println("DFSIterative(2):"); g.DFSIterative(2);
    System.out.println("DFS(2):"); g.DFS(2);
    System.out.println("countConnectedCoponents(): " + g.countConnectedComponents());
  }
}
