#ifndef __STACKS_H
#define __STACKS_H

#define EMPTY_STACK_ERR INT_MIN
#define MAX_RAND_VAL 1000

typedef struct Stack
{
  node *head;
  int size;
} Stack;

Stack *createStack(void);

Stack *destroyStack(Stack *s);

int isEmpty(Stack *s);

int isFull(Stack *s);

void push(Stack *s, int data);

int pop(Stack *s);

int peek(Stack *s);

int top(Stack *s);

void print_stack(Stack *s);

#endif
