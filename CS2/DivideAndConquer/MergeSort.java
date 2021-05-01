// Linked List implementation of Merge Sort
import java.io.*;
import java.util.*;

class Node
{
  int data;
  Node next;

  Node(int data)
  {
    this.data = data;
    this.next = null;
  }
}

public class MergeSort
{
  private Node head, tail;

  public void mergeSort()
  {
    this.head = mergeSort(this.head);
  }

  protected Node mergeSort(Node start)
  {
    // base case for empty or single node
    if (start == null || start.next == null)
      return start;

    Node hare = null;
    Node tortoise = null;

    // split linked list into halves
    // case for odd and even length linked list
    for (hare = start; hare != null && hare.next != null; hare = hare.next.next)
      tortoise = (tortoise == null) ? start : tortoise.next;

    Node mid = tortoise.next;
    tortoise.next = null;

    start = mergeSort(start);
    mid = mergeSort(mid);


    // Merge the two sorted linked list together
    Node head = null;
    Node tail = null;

    while (start != null || mid != null)
    {
      Node temp;

      if (start == null)
      {
        temp = mid;
        mid = mid.next;
      }
      else if (mid == null)
      {
        temp = start;
        start = start.next;
      }
      else if (start.data < mid.data)
      {
        temp = start;
        start = start.next;
      }
      else
      {
        temp = mid;
        mid = mid.next;
      }
      // tail insert the temp nodes
      if (head == null)
      {
        head = tail = new Node(temp.data);
        this.tail = this.head = head;
      }
      else
      {
        tail.next = new Node(temp.data);
        tail = tail.next;
        this.tail = tail;
      }
    }

    return head;
  }

  public void tailInsert(int data)
  {
    if (tail == null)
      head = tail = new Node(data);
    else
    {
      tail.next = new Node(data);
      tail = tail.next;
    }
  }

  public void print()
  {
    if (head == null)
      return;

    for (Node current = head; current != null; current = current.next)
      System.out.print((current.data) + ((current.next == null) ? "\n" : " " ));
  }

  public static void main(String [] args)
	{
		if (args.length < 1)
		{
			System.err.println("Proper syntax: java LinkedList <n>");
			return;
		}

		// Populate linked list with random integers.
		MergeSort list = new MergeSort();
		int n = Integer.parseInt(args[0]);

		for (int i = 0; i < n; i++)
			list.tailInsert((int)(Math.random() * 100) + 1);

		System.out.println("Unsorted list:");
		list.print();

		list.mergeSort();

		System.out.println("Sorted list (hopefully):");
		list.print();
	}
}
