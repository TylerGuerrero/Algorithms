// Queue implmentation using Linked List, FIFO(First In First Out)

// O(1) enqueue is achieved by inserting nodes at the tail of the linked list
// O(1) dequeue is achieved by removing nodes from the head of the linked list

// enqueue - puts element to the front of the Queue
// dequeue - deletes an element off the back of the Queue
// front - shows the element at the top of the Queue
// peek - is the same as front
// isEmpty - checks if the Queue is empty
// isFull - checks if the Queue is full
// print - prints the Queue

import java.io.*;

public class Queue<AnyType>
{
  private LinkedList<AnyType> list = new LinkedList<AnyType>();

  public void enqueue(AnyType data)
  {
    list.tailInsert(data);
  }

  public AnyType dequeue()
  {
    return list.deleteHead();
  }

  public AnyType front()
  {
    return list.showHead();
  }

  public AnyType peek()
  {
    return front();
  }

  public boolean isEmpty()
  {
    return list.isEmpty();
  }

  public boolean isFull()
  {
    return false;
  }

  public void print()
  {
    list.print();
  }

  public static void main(String [] args)
  {
    Queue<Integer> q1 = new Queue<Integer>();

    for (int i = 0; i < 10; i++)
    {
      int r = (int)(Math.random() * 100) + 1;
      System.out.println("Enqueuing ... " + r);
      q1.enqueue(r);
    }

    while (!q1.isEmpty())
      System.out.print(q1.dequeue() + " ");
    System.out.println("");

    Queue<String> q2 = new Queue<String>();

    q2.enqueue("hello");
    q2.enqueue("my");
    q2.enqueue("name");
    q2.enqueue("is");
    q2.enqueue("tyler");

    while (!q2.isEmpty())
      System.out.print(q2.dequeue() + " ");
    System.out.println();
  }
}
