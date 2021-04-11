import java.io.*;

class Node<AnyType>
{
  AnyType data;
  Node<AnyType> next;

  Node(AnyType data)
  {
    this.data = data;
    this.next = null;
  }
}

public class LinkedList<AnyType>
{
  private Node<AnyType> head, tail;

  public void headInsert(AnyType data)
  {
    if (head == null)
      head = tail = new Node<AnyType>(data);
    else
    {
      Node<AnyType> newHead = new Node<AnyType>(data);
      newHead.next = head;
      head = newHead;
    }
  }

  public void tailInsert(AnyType data)
  {
    if (tail == null)
      head = tail = new Node<AnyType>(data);
    else
    {
      tail.next = new Node<AnyType>(data);
      tail = tail.next;
    }
  }

  public AnyType deleteHead()
  {
    if (head == null)
      return null;

    AnyType retval = head.data;
    head = head.next;

    // case for single node
    if (head == null)
      tail = null;

    return retval;
  }

  public AnyType deleteTail()
  {
    if (tail == null)
      return null;
    // case for single node
    else if (head.next == null)
    {
      AnyType retval = head.data;
      head = tail = null;
      return retval;
    }
    else
    {
      Node<AnyType> current = head;
      while(current.next != tail)
        current = current.next;

      AnyType retval = tail.data;
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

    for (Node<AnyType> current = head; current != null; current = current.next)
      System.out.print(current.data + ((current.next == null) ? "\n" : " "));
  }

  public AnyType showHead()
  {
    if (head == null)
      return null;
    else
      return head.data;
  }

  public static void main(String [] args)
  {
    LinkedList<Integer> list = new LinkedList<Integer>();

    list.headInsert(43);
    list.headInsert(58);
    list.headInsert(52);
    list.tailInsert(33);
    list.tailInsert(19);
    list.headInsert(12);

    // Print the list to verify everything got in there correctly.
    list.print();

    list.deleteTail();
    list.deleteTail();
    list.print();

    while (!list.isEmpty())
    {
      list.deleteTail();
      list.print();
    }

    System.out.println();

    LinkedList<String> list2 = new LinkedList<String>();

    list2.headInsert("My");
    list2.headInsert("Name");
    list2.headInsert("is");
    list2.headInsert("Tyler");

    list2.print();

    while (!list2.isEmpty())
    {
      list2.deleteTail();
      list2.print();
    }
  }
}
