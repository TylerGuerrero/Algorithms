#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinkedList.h"
#include "Stacks.h"

Stack *createStack(void)
{
  Stack *s = malloc(sizeof(Stack));
  s->head = NULL;
  s->size = 0;
  return s;
}

Stack *destroyStack(Stack *s)
{
  if (s == NULL)
    return NULL;
  else if (s->head == NULL)
  {
    free(s);
    return NULL;
  }
  else
  {
    s->head = destroy_linked_list(s->head);
    free(s);
    return NULL;
  }
}

int isEmpty(Stack *s)
{
  return (s == NULL || s->size == 0);
}

int isFull(Stack *s)
{
  return 0;
}

void push(Stack *s, int data)
{
  if (s == NULL)
    return;

  s->head = head_insert(s->head, data);
  s->size++;
}

int pop(Stack *s)
{
  int retval;

  if (isEmpty(s))
    return EMPTY_STACK_ERR;

  retval = s->head->data;
  s->head = head_delete(s->head);
  s->size--;
  return retval;
}

int top(Stack *s)
{
  if (isEmpty(s))
    return EMPTY_STACK_ERR;

  return s->head->data;
}

int peek(Stack *s)
{
  return top(s);
}

void print_stack(Stack *s)
{
  node *current;
  int i;

  if (isEmpty(s))
    return;

  i = s->size - 1;
  current = s->head;

  while (current != NULL && i >= 0)
  {
    printf("+-----------+\n");
    printf("|  %-4d     |%s\n", current->data,
    ((i == s->size - 1) ? " <- Top of the Stack" : ""));
    printf("+-----------+\n");

    current = current->next;
    i--;
  }

  printf("\n\n");
}

int *create_array_with_nums(int n)
{
  int i;
  int *array = malloc(sizeof(int) * n);
  srand(time(NULL));

  for (i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND_VAL + 1;

  return array;
}

int main(void)
{
  int i, n = 12;
  int *array = create_array_with_nums(n);
  Stack *s = createStack();
  int p;

  for (i = 0; i < n; i++)
    push(s, array[i]);

  p = peek(s);
  printf("%d\n\n", p);

  print_stack(s);

  while(!isEmpty(s))
    printf("Popping %d\n", pop(s));

  s = destroyStack(s);
  free(array);

  return 0;
}
