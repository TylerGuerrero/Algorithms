import java.io.*;
import java.util.*;

public class Iterators
{
  //   Java offers three was of iterating through its collections
  //   classes (such as LinkedLists and ArrayLists). In this page, I
  //   explore the pros and cons of each style of iteration.
  public static void main(String [] args)
  {
    LinkedList<Integer> list = new LinkedList<Integer>();

    for (int i = 0; i < 10; i++)
    {
      int r = (int)((Math.random() * 100) + 1);
      System.out.println("Inserting " + r + "...");
      list.add(r);
    }

    // This approach has the benefit of being quite intuitive and readable, but
    // that .get() method is linear because it has to loop through the LinkedList,
    // starting at the head, to reach the ith element. As a result of the linear
    // nature of the .get() method, that for-loop ends up being O(n^2).

    // Note that if we used an ArrayList in this example instead of a LinkedList,
    // the for-loop would be O(n) instead of O(n^2). That's because there's an array
    // underlying each ArrayList. So, the ArrayList's .get() method is performing
    // an O(1) array access (after an O(1) check to make sure you're not asking
    // for an array index that's out of bounds).

    // Method 1
    // Big-O: O(n^2)
    for (int i = 0; i < list.size(); i++)
      System.out.print(list.get(i) + ((i == list.size() - 1) ? "\n" : " "));

    // The big benefit here is that the iterator traverses the linked list just
    // once, in a single pass, from head to tail. That's a stark contrast to the
    // .get() method, which starts at the beginning of the linked list each time
    // it's called. The while-loop in this approach is O(n), which is a drastic
    // improvement in runtime compared to the traditional for-loop in the previous
    // section.

    // Method 2
    // Big-O: O(n)
    Iterator itr = list.iterator();
    while (itr.hasNext())
      System.out.print(itr.next() + (itr.hasNext() ? " " : "\n"));

    // This fancy for-loop (called an "enhanced for-loop" or sometimes a "for-each
    // loop") uses an iterator behind the scenes. So, it has all the nice runtime
    // benefits of using an iterator, but none of the cumbersome syntax.

    // One downside here is that this approach doesn't give us a built-in way to
    // check how many elements we've processed and whether we've reached the last
    // element in the list. That's reflected my sloppy approach to the print
    // statements above, which results in an extraneous space after the last
    // element is printed.

    // Method 3
    // Big-O: O(n)
    for (Integer i : list)
      System.out.print(i + " ");
    System.out.println("");
  }
}
