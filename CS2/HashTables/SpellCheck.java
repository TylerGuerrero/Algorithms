// SpellCheck.java
// ===============
// An example of the usefulness of Java's HashSet class. There are many great
// collection classes in Java that you should familiarize yourself with. Here
// are two useful references to get you started with Java's collections:

import java.io.*;
import java.util.Iterator;
import java.util.HashSet;
import java.util.Scanner;


public class SpellCheck
{
  public static void main(String [] args) throws IOException
  {
    Scanner in = new Scanner(new File("dictionary.txt"));

    // 1) Cant have duplicate keys
    // 2) Only contains keys of the same type
    HashSet<String> hash = new HashSet<String>();

    while (in.hasNext())
      hash.add(in.next());

    String questionableWord = "irregardless";

    if (hash.contains(questionableWord))
      System.out.println("HashSet has the word " + questionableWord + " in it ");
    else
      System.out.println("HashSet does not have the word " + questionableWord + " in it");

    // 3 ways to iterate through a hashset
    Iterator itr = hash.iterator();
    while (itr.hasNext())
      System.out.println(itr.next());

    System.out.println("--------------------");
    for (String key : hash)
      System.out.println(key);
    System.out.println("--------------------");

    Object [] keys = hash.toArray();
    int j = 0;

    for (Object o : keys)
      System.out.println(++j + ": " + o);
  }
}
