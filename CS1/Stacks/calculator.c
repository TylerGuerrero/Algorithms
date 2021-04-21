#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPTY_STACK_ERR '\0'

// Stacks are LIFO structures (last in, first out), and they support the following operations:
//
// push()  -  push element onto the top of the stack
// pop()  -  removes the top item from the stack and returns its value
// isEmpty()  -  returns true of the stack is empty, false otherwise
// isFull()  -  returns true if the stack is full, false otherwise
// top(), peek()  -  returns the value at the top of the stack without popping it

// 0 index of the array is the bottom of the stack (push starting at 0 to n - 1 index)
// n - 1 index is the top of the stack.  (pop at n - 1 index)

typedef struct Stack
{
  char *array;
  int size;
  int capacity;
} Stack;

Stack *createStack(int capacity)
{
  Stack *s = malloc(sizeof(Stack));
  s->array = malloc(sizeof(char) * capacity);
  s->size = 0;
  s->capacity = capacity;
  return s;
}

Stack *destroyStack(Stack *s)
{
  if (s == NULL)
    return NULL;

  if (s->array == NULL)
  {
    free(s);
    return NULL;
  }

  free(s->array);
  free(s);
  return NULL;
}

int isEmpty(Stack *s)
{
  return (s == NULL || s->size == 0);
}

int isFull(Stack *s)
{
  return (s == NULL || s->size == s->capacity);
}

void push(Stack *s, char data)
{
  if (isFull(s))
  {
    printf("The Stack is full\n");
    return;
  }

  s->array[s->size++] = data;
}

char pop(Stack *s)
{
  int retval;

  if (isEmpty(s))
    return EMPTY_STACK_ERR;

  return s->array[--s->size];
}

char peek(Stack *s)
{
  if (isEmpty(s))
  {
    printf("Empty Stack\n");
    return EMPTY_STACK_ERR;
  }

  return s->array[s->size - 1];
}

int front(Stack *s)
{
  return peek(s);
}

void printStack(Stack *s)
{
  int i;

  if (isEmpty(s))
    return;

  for (i = s->size - 1; i >= 0; i--)
  {
    printf("+--------+\n");
    printf("|  %-4c  |%s\n", s->array[i], (i == s->size - 1) ?
            " <- Top of the stack" : "");
    printf("+--------+\n");
  }

  printf("\n\n");
}

int isNum(char ch)
{
  return (ch >= '0' && ch <= '9');
}

int Precedence(char ch)
{
  switch (ch)
  {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
  }

  return -1;
}

// Big-O: O(n), Space-Complexity: O(n)
char *infixToPostFix(char *exp)
{
  int i, k, len;

  // char stack
  Stack *s = createStack(strlen(exp));
  k = 0;

  for (i = 0; exp[i] != '\0'; i++)
  {
    // case 1: if it is a num output it
    if (isNum(exp[i]))
      exp[k++] = exp[i];
    // case 2: if it is a open parentheses
    else if (exp[i] == '(')
      push(s, exp[i]);
    // case for closed parentheses
    // at this point the operators are in the stack in greater order... so just pop
    // since all you want is postfix
    else if (exp[i] == ')')
    {
      while (!isEmpty(s) && peek(s) != '(')
        exp[k++] = pop(s);

      if (!isEmpty(s) && peek(s) != '(')
        return NULL;

      // pops the open parentheses
      pop(s);
    }
    // case for operators
    // you have to evaluate whether the operator on the top the stack is greater
    // then or equal to whats at the string at ith index cause if it is you pop
    // to get to postfix if not you push exp at ith index because it is greater then
    // the top of the stack
    else
    {
      while (!isEmpty(s) && (Precedence(peek(s)) >= Precedence(exp[i])))
        exp[k++] = pop(s);

      // push at this point becasue it greater then the operator on top the stack
      push(s, exp[i]);
    }
  }

  // pop the rest the stack
  while (!isEmpty(s))
    exp[k++] = pop(s);

  exp[k] = '\0';
  printf("%s\n", exp);

  s = destroyStack(s);
  return exp;
}

int evaluatePostfix(char *exp)
{
  int i, op1, op2;

  // int stack
  Stack *s = createStack(strlen(exp));

  for (i = 0; exp[i] != '\0'; i++)
  {
    // case 1: is a number
    if (isNum(exp[i]))
      push(s, exp[i] - '0');
    // cases for operators
    else
    {
      op1 = pop(s);
      op2 = pop(s);

      switch (exp[i])
      {
        case '+': push(s, op2 + op1); break;
        case '*': push(s, op2 * op1); break;
        case '-': push(s, op2 - op1); break;
        case '/': push(s, op2 / op1); break;
      }
    }
  }

  // pop becasue their will only be one element left
  // which is your result
  return pop(s);
}

int main(void)
{
  char *temp;
  char str[] = "3+8*6-(9+1)*2";
  char *exp = malloc(sizeof(char) * (strlen(str) + 1));

  strcpy(exp, str);
  temp = infixToPostFix(exp);
  printf("%d\n", evaluatePostfix(temp));
  free(exp);

  return 0;
}
