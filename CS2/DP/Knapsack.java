// DP SOLUTION ANATOMY
// 1) Combo of exhaustive search and greedy approach
// 2) Will compute subproblems and store them in our dp solution
// 3) The dp solution will have strong fidelity to our recurrence relation
// 4) The dimensions of our dp array will be strongly correlated to our inputs

// MEMOIZATION SOLUTION ANATOMY
// 1) base case
// 2) extra flavor of a base case to check for cached result
// 3) store result of recursive call in array or hashmap
// 4) return result

import java.io.*;
import java.util.*;
import java.awt.*;

class Treasure
{
  int weight, value;

  Treasure(int weight, int value)
  {
    this.weight = weight;
    this.value = value;
  }
}

public class Knapsack
{
  public static int knapsack(Treasure [] treasures, int capacity)
  {
    return knapsack(treasures, capacity, treasures.length);
  }

  // Big-O: Worst-Case: O(2^n), Best-Case: O(n), Space-Complexity: O(n)
  private static int knapsack(Treasure [] treasures, int capacity, int k)
  {
    if (capacity == 0 || k == 0)
      return 0;

    if (treasures[k - 1].weight <= capacity)
      return Math.max(
      knapsack(treasures, capacity - treasures[k - 1].weight, k - 1) + treasures[k - 1].value,
      knapsack(treasures, capacity, k - 1));
    else
      return knapsack(treasures, capacity, k - 1);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
  public static int knapsackMemo(Treasure [] treasures, int capacity)
  {
    HashMap<Point, Integer> memo = new HashMap<Point, Integer>();
    return knapsackMemo(treasures, capacity, treasures.length, memo);
  }

  // Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
  private static int knapsackMemo(Treasure [] treasures, int capacity, int k, HashMap<Point, Integer> memo)
  {
    // base case
    if (capacity == 0 || k == 0)
      return 0;

    // extra flavor of a base case to see cached result
    Integer result = memo.get(new Point(capacity, k));
    if (result != null)
      return result;

    // store recursive call in result and put it in a hashmap
    if (treasures[k - 1].weight <= capacity)
      result = Math.max(
        knapsack(treasures, capacity - treasures[k - 1].weight, k - 1) + treasures[k - 1].value,
        knapsack(treasures, capacity, k - 1)
      );
    else
      result = knapsack(treasures, capacity, k - 1);

    // return result
    memo.put(new Point(capacity, k), result);
    return result;
  }

  public static void main(String [] args)
  {
    // The expected result here is 19, from taking the treasures at indices
    // 1, 2, 3, and 5.
    Treasure [] treasures = new Treasure[] {
      new Treasure(4, 6),
      new Treasure(2, 4),
      new Treasure(3, 5),
      new Treasure(1, 3),
      new Treasure(6, 9),
      new Treasure(4, 7)
    };

    System.out.println(knapsack(treasures, 10));
    System.out.println(knapsackMemo(treasures, 10));
    //System.out.println(knapsack_dp(treasures, 10));
    //System.out.println(knapsack_dp_compressed(treasures, 10));
  }
}
