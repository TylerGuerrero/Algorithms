// ClosestPair.java
// ================
// A skeleton for the closest points algorithm.

import java.io.*;
import java.util.*;

class Point implements Comparable<Point>
{
	int x, y;

	Point(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	// Using Collections.sort() will sort by x-coordinate.
	public int compareTo(Point rhs)
	{
		return this.x - rhs.x;
	}

	// Returns the distance between two points. Using large x and y values
	// could cause integer overflow here. See note in main().
	public double distance(Point rhs)
	{
		int dx = this.x - rhs.x;
		int dy = this.y - rhs.y;

		return Math.sqrt((dx * dx) + (dy * dy));
	}

	public String toString()
	{
		return "(" + this.x + ", " + this.y + ")";
	}
}

public class ClosestPair
{
	// Returns minimum distance between any pair of points in the list. This
	// brute force approach is O(n^2).

	// Big-O: Worst-Case: O(n^2), Bets-Case: O(n^2), Space-Complexity: O(1)
	public static double smallestDeltaBruteForce(ArrayList<Point> points)
	{
		double delta = Double.MAX_VALUE;

		for (int i = 0; i < points.size(); i++)
			for (int j = i + 1; j < points.size(); j++)
				if (points.get(i).distance(points.get(j)) < delta)
					delta = points.get(i).distance(points.get(j));

		return delta;
	}

	// TODO: Sort indices 'lo' through 'hi' by y-coordinate. You might want
	//       to call this from your base case in smallestDeltaDivideAndConquer.
	//       I only ended up calling this from the base case and nowhere else.
	//       I implemented this as an O(n^2) method, but because it's only
	//       called with 2 <= n <= 3, the runtime is just a small constant.

	// Bubble-Sort Enhanced
	// 1) i = 0, j = 0
	// 2) loop through the array n - 1 - j times
	// 3) if (array[i] > array[i + 1]) then swap(array, i, i + 1)
	// 4) i++, j++

	// Big-O: Worst-Case: O(n^2), Best-Case: O(n), Space-Complexity: O(1)
	private static void sortByYCoordinate(ArrayList<Point> points, int lo, int hi)
	{
		boolean swapped = true;
		int j = 0;

		while (swapped)
		{
			swapped = false;
			for (int i = lo; i <= hi - 1 - j; i++)
				if (points.get(i).y > points.get(i + 1).y)
				{
					Collections.swap(points, i, i + 1);
					swapped = true;
				}
			j++;
		}
	}

	// TODO: Return the minimum distance between any pair of points from indices
	//       'lo' through 'hi'. You might want to call this from your base case
	//       in smallestDeltaDivideAndConquer. I implemented this as an O(n^2)
	//       method, but because it's only called with 2 <= n <= 3, the runtime
	//       is just a small constant.

	// Big-O: Worst-Case: O(n^2), Best-Case: O(n^2), Space-Complexity: O(1)
	private static double smallestDeltaBruteForce(ArrayList<Point> points, int lo, int hi)
	{
		double delta = Double.MAX_VALUE;

		for (int i = lo; i <= hi; i++)
			for (int j = i + 1; j <= hi; j++)
				if (points.get(i).distance(points.get(j)) < delta)
					delta = points.get(i).distance(points.get(j));

		return delta;
	}

	// Assumes indices 'lo' through 'mid' are sorted by y-coordinate, and also
	// that 'mid'+1 through 'hi' are sorted by y-coordinate, and merges those
	// two halves together so that 'lo' through 'hi' are sorted by y-coordinate.
	// This should be called from smallestDeltaDivideAndConquer. You have to
	// compute 'mid' yourself.

	// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(n)
	private static void mergeByY(ArrayList<Point> points, int lo, int hi)
	{
		int mid = lo + (hi - lo) / 2;
		int i = lo;
		int j = mid + 1;
		int k = 0;

		Point [] aux = new Point[hi - lo + 1];

		while (i <= mid || j <= hi)
		{
			if (i > mid)
				aux[k++] = points.get(j++);
			else if (j > hi)
				aux[k++] = points.get(i++);
			else if (points.get(i).y < points.get(j).y)
				aux[k++] = points.get(i++);
			else
				aux[k++] = points.get(j++);
		}

		for (i = lo; i <= hi; i++)
			points.set(i, aux[i - lo]);
	}

	// Returns the minimum distance between any pair of points in the list from
	// indices 'lo' through 'hi'. This also (re-)sorts the list by y-coordinate
	// as it returns from each recursive call.

	// Big-O: Worst-Case: O(nlogn), Best-Case: O(nlogn), Space-Complexity: O(n)
	private static double smallestDelta(ArrayList<Point> points, int lo, int hi)
	{
		int len = hi - lo + 1;

		if (len <= 3)
		{
			// What are the two things you need to do if you hit a base case?

			// By the way, you could use n <= 2 as your base case, but then if
			// you have three points, one of your recursive calls below would
			// just receive *one* of those points, and that's kind of awkward,
			// because there's nothing to compare its distance to if there's
			// just one point.
			double delta = smallestDeltaBruteForce(points, lo, hi);
			sortByYCoordinate(points, lo, hi);
			return delta;
		}

		// Make recursive calls to find delta1 and delta2.
		int mid = lo + (hi - lo) / 2;
		double deltaLeft = smallestDelta(points, lo, mid);
		double deltaRight = smallestDelta(points, mid + 1, hi);
		double delta = Math.min(deltaLeft, deltaRight);

		mergeByY(points, lo, hi);

		// Check the distance from each point to the seven points after it in
		// the array list (i.e., the seven points above it when sorted by y-
		// coordinate). If it's closer than 'delta' to any of those points,
		// update delta.
		for (int i = 0; i < points.size(); i++)
			for (int j = i + 1; j < Math.min(i + 7, points.size()); j++)
				if (points.get(i).distance(points.get(j)) < delta)
					delta = points.get(i).distance(points.get(j));

		return delta;
	}

	// Returns the minimum distance between any pair of points in the list.

	// Big-O: Worst-Case: O(nlogn), Best-Case: O(nlogn), Space-Complexity: O(n)
	public static double smallestDeltaDivideAndConquer(ArrayList<Point> points)
	{
		// If we have 0 or 1 values, there's no smallest distance.
		if (points.size() < 2)
			return Double.MIN_VALUE;

		// TODO: What should you do before kicking off this first call to the
		//       private method?
		Collections.sort(points);
		return smallestDelta(points, 0, points.size() - 1);
	}

	// Checks whether the array list of points is sorted by y-coordinate.
	// Returns true if so, false otherwise.

	// Big-O: Worst-Case: O(n), Best-Case: O(n), Space-Complexity: O(1)
	public static boolean isSortedByYCoordinate(ArrayList<Point> points)
	{
		for (int i = 0; i < points.size() - 1; i++)
			if (points.get(i).y > points.get(i + 1).y)
				return false;

		return true;
	}

	public static void main(String [] args)
	{
		// If you specify a command line argument, that will be used as the
		// number of randomly generated points. Otherwise, we default to 10.
		int n = (args.length < 1) ? 10 : Integer.parseInt(args[0]);

		ArrayList<Point> points = new ArrayList<>();

		// NOTE: You don't want to go far beyond 30,000 for the max x and y
		//       values you generate for your points, because you don't want
		//       your distance formula to potentially cause integer overflow.
		for (int i = 0; i < n; i++)
		{
			int x = (int)(Math.random() * 10000);
			int y = (int)(Math.random() * 10000);

			points.add(new Point(x, y));
		}

		System.out.println("Points (unsorted):");
		System.out.println("==================");
		for (Point p : points)
			System.out.println(p);

		// Divide and conquer algorithm.
		System.out.println("\nFinding minimum distance (divide and conquer)...");
		System.out.println("result: " + smallestDeltaDivideAndConquer(points));

		// Check whether coordinates are sorted by y-coordinate upon returning
		// from divide and conquer algorithm.
		if (isSortedByYCoordinate(points))
			System.out.println("\n* Points are successfully sorted by y-coordinate. Nice!");
		else
			System.out.println("\n* Oh no! Points are not sorted by y-coordinate. :(");

		System.out.println("\nFinding minimum distance (brute force)...");
		System.out.println("result: " + smallestDeltaBruteForce(points));
	}
}
