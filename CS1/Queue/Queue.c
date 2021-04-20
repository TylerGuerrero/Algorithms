#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// FIFO (First In and First Out)

// createQueue - creates a Queue
// destroyQueue - destroys the Queue
// enqueue - inserts a elemnet to the front of the queue - tail_insert
// dequeue - deletes a elemnet at the front of the queue - head_delete
// front - shows the elemnet at the front of the Queue
// top - shows the element at the front of queue
// printQueue - prints the queue

#include "LinkedList.h"
#include "Queue.h"

Queue *createQueue(void)
{
  Queue *q = malloc(sizeof(Queue));
  q->list = create_list();
  q->size = 0;
  return q;
}

Queue *destroyQueue(Queue *q)
{
  if (q == NULL)
    return NULL;
  else if (q->list == NULL)
  {
    free(q);
    return NULL;
  }
  else
  {
    q->list = destroy_linked_list(q->list);
    free(q);
    return NULL;
  }
}

int isEmpty(Queue *q)
{
  return (q == NULL || q->size == 0);
}

int isFull(Queue *q)
{
  return 0;
}

void enqueue(Queue *q, int data)
{
  if (q == NULL)
    return;

  tail_insert(q->list, data);
  q->size++;
}

int dequeue(Queue *q)
{
  int retval;

  if (isEmpty(q))
    return EMPTY_QUEUE_ERR;

  retval = q->list->head->data;
  head_delete(q->list);
  q->size--;
  return retval;
}

int front(Queue *q)
{
  if (isEmpty(q))
    return EMPTY_QUEUE_ERR;

  return q->list->head->data;
}

int peek(Queue *q)
{
  return front(q);
}

void printQueue(Queue *q)
{
  if (isEmpty(q))
  {
    printf("Epmty list\n");
    return;
  }

  print_linked_list(q->list);
}

// Just a trivial test of the queue's functionality.
int main(void)
{
	int i, r, n = 10;
	Queue *q = createQueue();

	srand(time(NULL));

	// Enqueue a few elements.
	for (i = 0; i < n; i++)
	{
		printf("Enqueueing %d...\n", r = rand() % 100 + 1);
		enqueue(q, r);
    printQueue(q);
	}

  printf("\n\n");

	// Empty out the queue.
	while (!isEmpty(q))
  {
    printQueue(q);
    dequeue(q);
  }

	// Exercise: Write this function yourself.
	destroyQueue(q);

	return 0;
}
