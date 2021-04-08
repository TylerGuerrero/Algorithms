import java.io.*;
import java.util.*;

class VanillaNode
{
  int data;
  VanillaNode next;

  VanillaNode(int data)
  {
    this.data = data;
    this.next = null;
  }
}

public class VanillaLinkedList
{
  private VanillaNode head, tail;

  public void tailInsert(int data)
  {
    if (tail == null)
      head = tail = new VanillaNode(data);
    else
    {
      tail.next = new VanillaNode(data);
      tail = tail.next;
    }
  }

  public void headInsert(int data)
  {
    if (head == null)
      head = tail = new VanillaNode(data);
    else
    {
      VanillaNode newHead = new VanillaNode(data);
      newHead.next = head;
      head = newHead;
    }
  }

  public Integer deleteHead()
  {
    if (head == null)
      return null;

    int retval = head.data;
    head = head.next;

    // case for single node
    if (head == null)
      tail = null;

    return retval;
  }

  public Integer deleteTail()
  {
    if (tail == null)
      return null;
    // case for single node
    else if (head.next == null)
    {
      int retval = head.data;
      head = tail = null;
      return retval;
    }
    else
    {
      VanillaNode current = head;
      while (current.next != tail)
        current = current.next;

      int retval = tail.data;
      tail = current;
      tail.next = null;
      return retval;
    }
  }

  public boolean isEmpty()
  {
    return (head == null);
  }

  public void print()
  {
    if (head == null)
      return;

    for (VanillaNode current = head; current != null; current = current.next)
      System.out.print(current.data + ((current.next != null) ? " " : "\n"));
  }

  public static void main(String [] args)
  {
    VanillaLinkedList list = new VanillaLinkedList();

    list.headInsert(43);
    list.headInsert(58);
    list.headInsert(52);
    list.tailInsert(33);
    list.tailInsert(19);
    list.headInsert(12);

    // Print the list to verify everything got in there correctly.
    list.print();

    list.deleteTail();
    list.deleteHead();
    list.print();

    while (!list.isEmpty())
    {
      list.deleteTail();
      list.print();
    }
  }
}
