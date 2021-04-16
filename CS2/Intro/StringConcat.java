import java.io.*;
import java.util.*;

public class StringConcat
{
  // Given the fact that strings are immutable in Java, the following Java method
  // needs to create an entirely new string of length (m + n), where m is the
  // length of str1 and n is the length of str2. (Java does not just go to wherever
  // str1 is being stored and tack str2 onto the end of it. Java creates a whole
  // new string and copies both str1 and str2 into it.) That means the runtime of
  // the following method is O(m + n).

  // Big-O: O(n + m)
  public static String myConcatenator(String str1, String str2)
  {
    str1 += str2;
    return str1;
  }

  // Big-O: O(n^2)
  public static String thisMethodIsOrderedSquared(String str1, String str2)
  {
    for (int i = 0; i < str2.length(); i++)
      // The following concatenation is expensive in Java.
      // This creates an entirely new string at each iteration
      // of the for-loop!!
      str1 += str2.charAt(i);

    return str1;
  }

  // Big-O: O(n)
  public static String fasterConcatenation(String str)
  {
    StringBuilder builder = new StringBuilder();
    for (int i = 0; i < str.length(); i++)
      builder.append(str.charAt(i));

    return builder.toString();
  }

  // Big-O: O(n)
  public static String fasterConcatenationOptimized(String str1, String str2)
  {
    StringBuilder builder = new StringBuilder(str1.length() + str2.length());
    for (int i = 0; i < str1.length(); i++)
      builder.append(str1.charAt(i));

    for (int i = 0; i < str2.length(); i++)
      builder.append(str2.charAt(i));

    return builder.toString();
  }

  // Big-O: O(n^2)
  public static String slowStringBuilderApproach(String s)
  {
   String newString = "";
   for (int i = 0; i < s.length(); i++)
   {
      StringBuilder builder = new StringBuilder(newString);
      builder.append(s.charAt(i));
      newString = builder.toString();
   }
   return newString;
 }
}
