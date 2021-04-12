// Person.java
// ===========
// An example of interfaces in Java. We develop a class that implements the
// Comparable interface. Whereas extending a class in Java allows us the
// *option* of overriding methods, implementing an interface *requires* us to
// override the methods defined by that interface.

// This is immensely useful because it allows us to write generic methods that
// require a class to have defined a particular method, but say nothing about
// the superclasses that these classes must extend. Therefore, we do not have to
// mess with the inheritance chain.

// Implementing the Comparable interface allows us to call a variety of sort()
// methods in Java. All we have to do is override a compareTo() method. In
// earlier versions of Java, we implemented the following compareTo() method:

//       public class MyClass implements Comparable
//       {
//          public int compareTo(Object o)
//          {
//             // ...
//          }
//       }

// As of Java 5, the Comparable interface is generic. This is pretty awesome
// because the compiler can now check compareTo() calls at compile time for
// type mismatches. Before, when the method could take any type of object, type
// mismatches couldn't be detected at compile time, and could easily cause
// runtime errors.

// We now typically implement the Comparable interface with a type restriction:

//       public class MyClass implements Comparable<MyClass>
//       {
//          public int compareTo(MyClass rhs)
//          {
//             // ...
//          }
//       }

import java.util.*;
import java.io.*;

// when using the interface Comparable you will end up using the object
// you implemented in a Collections class such ArrayList, LinkedList, ..etc

public class Person implements Comparable<Person>
{
  private int birthDay, birthMonth, birthYear;
  private String firstName, lastName;

  // We will order our Person objects by birthday. We want older persons to
  // come before younger persons in sorted order, so we do the following:

  // Return a negative integer if 'this' was born before 'rhs.' Return a
  // positive integer if 'this' was born after 'rhs'. Return zero if they
  // both share the same birthday.
  public int compareTo(Person rhs)
  {
    if (this.birthYear != rhs.birthYear)
      return this.birthYear - rhs.birthYear;
    else if (this.birthMonth != rhs.birthMonth)
      return this.birthMonth - rhs.birthMonth;
    else
      return this.birthDay - rhs.birthDay;
  }

  Person(String name, String birthday)
  {
		// The last word in the 'name' string will be the last name. Everything
		// else will be the first name. For example:

		// "Sean Szumlanski" => firstName = Sean
		//                      lastName  = Szumlanski

		// "Regulus Arcturus Black" => firstName = Regulus Arcturus
		//                             lastName  = Black
    int splitPoint = name.lastIndexOf(' ');
    this.firstName = name.substring(0, splitPoint);
    this.lastName = name.substring(splitPoint);

    // The String class in Java has a handy split() method that splits one
		// long string up into an array of individual strings, using some token
		// as a delineator. Here, we split dates up by the slash (/) character.
		// For example:

		// "01/30/1961".split("/") => { "01", "30", "1961" }
    String [] numbers = birthday.split("/");
    this.birthMonth = Integer.parseInt(numbers[0]);
    this.birthDay = Integer.parseInt(numbers[1]);
    this.birthYear = Integer.parseInt(numbers[2]);
  }

  public String toString()
  {
    return "(" + String.format("%02d", this.birthMonth) +
           "/" + String.format("%02d", this.birthDay) +
           "/" + String.format("%02d", this.birthYear) + ")" +
           " " + this.firstName + "," + this.lastName;
  }

  public static void main(String [] args)
  {
    // here's another fantastic Java container: an array that grows dynamically
    ArrayList<Person> list = new ArrayList<Person>();

    // add some Person objects to the ArrayList
    list.add(new Person("Cada St-Merrein", "04/22/1961"));
    list.add(new Person("Regulus Arcturus Black", "01/30/1961"));
    list.add(new Person("Perceval Thoreau", "08/08/1450"));
    list.add(new Person("Magdeleine Corriander Grabb", "05/19/1960"));

    // print the unsorted ArrayList
    System.out.println("Unsorted List");
    for (Person p : list)
      System.out.println(p);

    Collections.sort(list);

    System.out.println("");
    System.out.println("Sorted List");
    for (Person p : list)
      System.out.println(p);

    Collections.shuffle(list);

    // Conversion of a collections class to object array
    Person [] array = new Person[list.size()];
    for (int i = 0; i < list.size(); i++)
      array[i] = list.get(i);

    System.out.println("");
    System.out.println("Unsorted List");
    for (Person p : array)
      System.out.println(p);

    // sort an array
    Arrays.sort(array);

    System.out.println("");
    System.out.println("Sorted List");
    for (Person p : array)
      System.out.println(p);
  }
}
