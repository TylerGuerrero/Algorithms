#ifndef __QUEUE_H
#define __QUEUE_H

#define EMPTY_QUEUE_ERR INT_MIN

typedef struct Queue
{
  int size;
  LinkedList *list;
} Queue;

Queue *createQueue(void);

Queue *destroyQueue(Queue *q);

int isEmpty(Queue *q);

int isFull(Queue *q);

void enqueue(Queue *q, int data);

int dequeue(Queue *q);

int front(Queue *q);

int peek(Queue *q);

void printQueue(Queue *q);

#endif
