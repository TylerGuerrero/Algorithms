import java.io.*;
import java.util.Scanner;
import java.util.HashMap;
import java.util.Set;
import java.util.ArrayList;

// HASHMAP
// 1) HashMaps can contain duplicates
// 2) (key, value) pairs that have their own types
// 3) the methods of hashmap input types have to match the (key, value) types

public class WordCount
{
  public void insertOne(ArrayList<String> list)
  {
    HashMap<String, Integer> map = new HashMap<String, Integer>();

    for (String str : list)
    {
      if (map.containsKey(str))
        map.put(str, map.get(str) + 1);
      else
        map.put(str, 1);
    }
  }

  public void insertTwo(ArrayList<String> list)
  {
    HashMap<String, Integer> map = new HashMap<String, Integer>();

    for (String str : list)
    {
      Integer i = map.get(str);

      if (i != null)
        map.put(str, i + 1);
      else
          map.put(str, 1);
    }
  }

  public void insertThree(ArrayList<String> list)
  {
    HashMap<String, Integer> map = new HashMap<String, Integer>();

    for (String str : list)
      map.put(str, map.getOrDefault(str, 0) + 1);
  }

  public static void main(String [] args) throws IOException
  {
    Scanner in = new Scanner(new File("corpus.txt"));
    HashMap<String, Integer> map = new HashMap<String, Integer>();

    while (in.hasNext())
    {
      String str = in.next();

      // insert 1
      if (map.containsKey(str))
        map.put(str, map.get(str) + 1);
      else
        map.put(str, 1);

      // insert 2, more efficient
      // Integer i = map.get(str);
      // if (i != null)
      //   map.put(str, i + 1);
      // else
      //   map.put(str, 1);

      // insert 3
      // map.put(str, map.getOrDefault(str, 0) + 1)
    }

    String questionableWord = "silly";
    if (map.containsKey(questionableWord))
      System.out.println(questionableWord + ": (" + map.get(questionableWord) + ") times");
    else
      System.out.println(questionableWord + " is not in the dictionary");

    // creates a set of keys from the hash map (key, value) pairs
    // Print the (key, value) pairs
    Set<String> keys = map.keySet();
    for (String key : keys)
      System.out.println(key + ": (" + map.get(key) + ")");
  }
}
