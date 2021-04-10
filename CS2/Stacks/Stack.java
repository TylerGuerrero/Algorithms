// Stack implmentation using Linked List

// O(1) push is achieved by inserting nodes at the head of the linked list
// O(1) pop is achieved by removing nodes from the head of the linked list

// push - pushes element to the top of the stack
// pop - deletes an element off the top of the stack
// top - shows the element at the top of the stack
// peek - is the same as top
// isEmpty - checks if the stack is empty
// isFull - checks if the stack is full
// print - prints the stack

public class Stack<AnyType>
{
  private LinkedList<AnyType> list = new LinkedList<AnyType>();

  public void push(AnyType data)
  {
    list.headInsert(data);
  }

  public AnyType pop()
  {
    return list.deleteHead();
  }

  public AnyType top()
  {
    return list.showHead();
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
    Stack<Integer> s1 = new Stack<Integer>();

    for (int i = 0; i < 10;  i++)
    {
      int r = (int)(Math.random() * 100) + 1;
      System.out.println("Pushing " + r + "...");
      s1.push(r);
    }

    while (!s1.isEmpty())
      System.out.print(s1.pop() + " ");
    System.out.println();

    Stack<String> s2 = new Stack<String>();

    // push some strings onto the stack
    s2.push("business");
    s2.push("nobody's");
    s2.push("like");
    s2.push("popping");
    s2.push("and");
    s2.push("pushing");

    while (!s2.isEmpty())
      System.out.print(s2.pop() + " ");
    System.out.println();
  }
}
