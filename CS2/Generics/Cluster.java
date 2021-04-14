// Cluster.java
// ============
// In this example, we write a generic class (i.e., a class that deals with
// objects of any type) that calls Collections.sort() on a collection of that
// object type. In order to call Collections.sort(), we must ensure that the
// object type being sorted implements Comparable. So, we extend our typical
// generic syntax from this:

//    public class MyClass<AnyType> {
//
//       Collection<AnyType> myCollection;
//
//       public void sort() {
//          Collections.sort(myCollection);  // compile-time error! what if
//       }                                   // AnyType is not Comparable?
//    }

// ...to this syntax, which specifies that AnyType implements Comparable:
//
//    public class MyClass<AnyType extends Comparable> {
//
//       Collection<AnyType> myCollection;
//
//       public void sort() {
//          Collections.sort(myCollection);  // it's now okay to call sort()
//       }                                   // because we know AnyType is
//    }                                      // Comparable.

// Now the compiler will check at compile time to ensure that any time we
// create an object of MyClass, the AnyType parameter is a class that implements
// Comparable.

// Notice that we used "extends Comparable" above instead of "implements
// Comparable." That's just how Java does. When we implement an interface, we
// use "implements." When dealing with type parameters like this, we drop the
// distinction between extending a superclass and implementing an interface, and
// just tell Java that the class in question "extends" whatever superclass /
// interface we're dealing with.

// But wait. There's one more problem. What we saw earlier is that Comparable is
// now generic in Java. So, if we create SomeClass, we don't say that it
// implements Comparable; we say that it implements Comparable<SomeClass>. So,
// let's be more specific with that type parameter attached to our new generic
// class:

//    public class MyClass<AnyType extends Comparable<AnyType>> {
//
//       Collection<AnyType> myCollection;
//
//       public void sort() {
//          Collections.sort(myCollection);
//       }
//    }

// That's the syntax we'll use here to create a generic container called a
// Cluster. The Cluster isn't really doing anything exciting in terms of how
// it's organizing data. It's just a basic container with an ArrayList inside,
// and all you can really do is put things in it and sort them, but it gets the
// point across about how to mix generics and Comparable.

import java.io.*;
import java.util.*;

class Bauble
{
  public void bauble()
  {
    System.out.println("Bauble bauble !!!");
  }
}

public class Cluster<AnyType extends Comparable<AnyType>>
{
  ArrayList<AnyType> list;

  Cluster(int capacity)
  {
    list = new ArrayList<AnyType>(capacity);
  }

  public void put(AnyType object)
  {
    list.add(object);
  }

  public void sort()
  {
    Collections.sort(list);
  }

  public void print()
  {
    for (AnyType o : list)
      System.out.println(o);
  }

  public static void main(String [] args)
  {
    Cluster<Person> myCluster = new Cluster<Person>(4);

    // Throw some stuff into the cluster.
		myCluster.put(new Person("Cada St-Merrein", "04/22/1961"));
		myCluster.put(new Person("Regulus Arcturus Black", "01/30/1961"));
		myCluster.put(new Person("Perceval Thoreau", "08/08/1450"));
		myCluster.put(new Person("Magdeleine Corriander Grabb", "05/19/1960"));

    System.out.println("Unsorted List");
    System.out.println("==============");
    myCluster.print();

    myCluster.sort();

    System.out.println("");
    System.out.println("Sorted List");
    System.out.println("==============");
    myCluster.print();

    // NOTE: If you uncomment the following line, the code will *not*
		// compile, because Bauble does not implement Comparable! The way the
		// Cluster class is declared creates a contract. We can only create
		// Cluster objects that hold Comparable objects.
		//
		// Cluster<Bauble> myBaubles = new Cluster<>();

    System.out.println("");
    
    // This is just for fun.
    Bauble bauble = new Bauble();
    bauble.bauble();
  }
}
