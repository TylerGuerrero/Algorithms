// Hashable.java
// =============
// An example of a class that can serve as the key type for any of Java's hash
// collections. Some important methods mentioned in this code include:

// Used by Java's hash collections. Returns the hash value for an object of this class.
// public int hashCode() { ... }

// Used to print an object of this class when used in a String context.
// public String toString() { ... }

// Used to check objects of this class for equality. See link on this topic below.
// public boolean equals(Object o) { ... }

import java.io.*;
import java.util.*;

public class Hashable
{
  private String name;

  // Constructor. Nothing fancy to see here.
  Hashable(String name)
  {
    this.name = name;
  }

  // The inclusion of this method allows us to use Hashable objects as keys for
  // hash sets and hash maps. That's all you have to do to make your classes
  // hashable: write a public int hashCode() method. Strings have a built-in
  // hashCode() method that I'm calling here so that I don't have to write a
  // new one. :)
  public int hashCode()
  {
    return this.name.hashCode();
  }

  public String toString()
  {
    return this.name;
  }

  // Well, that's weird. Bran is in the output twice. Shouldn't the put()
  // method have updated the key-value pair (Bran, 1) with (Bran, 2)?

  // The answer is, no! The hash map has no way of knowing that these two
  // Hashable objects are identical. For that, we need an equals() method
  // specifically designed to test the equality of two Hashable objects.

  // Note that the hashCode method doesn't tell us whether two objects are
  // equal. It's always possible for different elements to have the same
  // hash value. Remember from CS1 that this is called a "collision."

  // Try adding this method to the Hashable class:
  public boolean equals(Object o)
  {
    if (o instanceof Hashable)
    {
      Hashable h = (Hashable)(o);
      return this.name.equals(h.name);
    }

    return false;
  }

  // Note that the equals() method MUST be written to take an Object
  // argument, not a more specific class. E.g., equals(Hashable h) would
  // be incorrect; it could have some undesired side effects.

  // Here is a wonderful, detailed discussion of how to properly implement
  // the equals() method: http://www.artima.com/lejava/articles/equality.html

  public static void main(String [] args)
  {
    HashMap<Hashable, Integer> map = new HashMap<Hashable, Integer>();

    map.put(new Hashable("Sean"), 1);
    map.put(new Hashable("Arya"), 1);
    map.put(new Hashable("Robb"), 1);
    map.put(new Hashable("Bran"), 1);
    map.put(new Hashable("Bran"), 2);

    Set<Hashable> keys = map.keySet();
    for (Hashable h : keys)
      System.out.println(h + ": " + "(" + map.get(h) + ")");
  }
}
