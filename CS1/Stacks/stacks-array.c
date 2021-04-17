#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPTY_STACK_ERR INT_MIN

// Stacks are LIFO structures (last in, first out), and they support the following operations:

// push()  -  push element onto the top of the stack
// pop()  -  removes the top item from the stack and returns its value
// isEmpty()  -  returns true of the stack is empty, false otherwise
// isFull()  -  returns true if the stack is full, false otherwise
// top(), peek()  -  returns the value at the top of the stack without popping it
// print_stack() - prints the stack

// 0 index of the array is the bottom of the stack (push starting at 0 to n - 1 index)
// n - 1 index is the top of the stack.  (pop at n - 1 index)

typedef struct Stack
{
  int *array;
  int size;
  int capacity;
} Stack;

Stack *createStack(int capacity)
{
  Stack *s = malloc(sizeof(Stack));
  s->array = malloc(sizeof(int) * capacity);
  s->size = 0;
  s->capacity = capacity;
  return s;
}

Stack *destroyStack(Stack *s)
{
  if (s == NULL)
    return NULL;
  else if (s->array == NULL)
  {
    free(s);
    return NULL;
  }
  else
  {
    free(s->array);
    free(s);
    return NULL;
  }
}

int isEmpty(Stack *s)
{
  return ((s == NULL) || (s->size == 0));
}

int isFull(Stack *s)
{
  return ((s == NULL) || (s->size == s->capacity));
}

void push(Stack *s, int data)
{
  if (isFull(s))
  {
    printf("Stack is Empty\n");
    return;
  }
  else
    s->array[s->size++] = data;
}

int pop(Stack *s)
{
  if (isEmpty(s))
    return EMPTY_STACK_ERR;

  return s->array[--s->size];
}

int top(Stack *s)
{
  if (isEmpty(s))
  {
    printf("Empty Stack\n");
    return EMPTY_STACK_ERR;
  }

  return s->array[s->size - 1];
}

int peek(Stack *s)
{
  return top(s);
}

void printStack(Stack *s)
{
  int i;

  if (isEmpty(s))
    return;

  for (i = s->size - 1; i >= 0; i--)
  {
    printf("+----------+\n");
    printf("|    %-4d  |%s\n", s->array[i],
    ((i == s->size - 1) ? " <- Top of the stack" : ""));
    printf("+----------+\n");
  }

  printf("\n\n");
}

// Print list of commands for menu-driven interface.
void printMenu(void)
{
	printf("\n");
	printf("Stack ops:\n");
	printf("\n");
	printf("  new <n>    -- create a new stack with capacity set to <n>\n");
	printf("  destroy    -- completely destroy the current stack\n");
	printf("  push <n>   -- push <n> onto the stack\n");
	printf("  pop        -- pops the top element off the stack\n");
	printf("  peek       -- prints the stack's top element without removing it\n");
	printf("  empty      -- indicates whether the stack is empty\n");
	printf("  full       -- indicates whether the stack is full\n");
}

void reverse_string(char *str)
{
  char temp;

  if (str == NULL)
    return;

  int left = 0;
  int right = strlen(str) - 1;

  // case for odd or even length array
  while (left <= right)
  {
    temp = str[left];
    str[left++] = str[right];
    str[right--] = temp;
  }
}

int main(void)
{
	char buffer[128]; int n;
	Stack *myStack = NULL;

	printMenu();
	printf("\n");

	// This loop is poorly commented, but hopefully it's fairly easy to follow.
	while (1)
	{
		printf("Enter a command ('?' for help, or 'exit' to quit).\n");
		printf("%% ");

		scanf("%s", buffer);

		if (strcmp(buffer, "?") == 0)
		{
			printMenu();
		}

		else if (strcmp(buffer, "new") == 0)
		{
			if (myStack != NULL)
				destroyStack(myStack);

			scanf("%d", &n);
			myStack = createStack(n);
		}

		else if (strcmp(buffer, "destroy") == 0)
		{
			if (myStack != NULL)
				myStack = destroyStack(myStack);
		}

		else if (strcmp(buffer, "push") == 0)
		{
			scanf("%d", &n);
			push(myStack, n);
		}

		else if (strcmp(buffer, "pop") == 0)
		{
			n = pop(myStack);

			if (n != EMPTY_STACK_ERR)
				printf("\n   -> popped %d\n", n);
		}

		else if (strcmp(buffer, "peek") == 0 || strcmp(buffer, "top") == 0)
		{
			n = peek(myStack);

			if (n != EMPTY_STACK_ERR)
				printf("\n   -> peek: %d\n", n);
		}

		else if (strcmp(buffer, "empty") == 0)
		{
			if (isEmpty(myStack))
				printf("\n   -> stack is empty\n");
			else
				printf("\n   -> stack is not empty\n");
		}

		else if (strcmp(buffer, "full") == 0)
		{
			if (isFull(myStack))
				printf("\n   -> stack is full\n");
			else
				printf("\n   -> stack is not full\n");
		}

		else if (strcmp(buffer, "exit") == 0)
		{
			break;
		}

		// Print the stack after each command.
		printStack(myStack);
		printf("\n");
	}

	// Clean up after yourself.
	destroyStack(myStack);

	return 0;
}
