#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_RAND_VAL 1000

typedef struct node
{
  int data;
  struct node *next;
  struct node *prev;
} node;

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->data = data;
  return new_node;
}

node *head_insert(node *head, int data)
{
  node *new_head;

  if (head == NULL)
    return create_node(data);

  new_head = create_node(data);
  new_head->next = head;
  head->prev = new_head;
  return new_head;
}

node *head_delete(node *head)
{
  node *new_head;

  if (head == NULL)
    return NULL;

  new_head = head->next;
  free(head);

  // case for last node
  if (new_head == NULL)
    return NULL;

  new_head->prev = NULL;
  return new_head;
}

node *tail_insert(node *head, int data)
{
  node *current, *new_tail;

  if (head == NULL)
    return create_node(data);

  current = head;
  while (current->next != NULL)
    current = current->next;

  new_tail = create_node(data);
  current->next = new_tail;
  new_tail->prev = current;
  return head;
}

node *tail_delete(node *head)
{
  node *current, *new_tail;

  if (head == NULL)
    return NULL;
  // case for single node
  else if (head->next == NULL)
  {
    free(head);
    return NULL;
  }
  else
  {
    current = head;
    while (current->next != NULL)
      current = current->next;

    new_tail = current->prev;
    new_tail->next = NULL;
    free(current);
    return head;
  }
}

node *destroy_list(node *head)
{
  node *current, *temp;

  if (head == NULL)
    return NULL;

  current = head;
  while (current != NULL)
  {
    temp = current->next;
    free(current);
    current = temp;
  }

  return NULL;
}

void print_list(node *head)
{
  if (head == NULL)
    return;

  for (head = head; head != NULL; head = head->next)
    printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
}

node *deleteNth(node *head, int n)
{
  node *current, *temp;
  int i;

  if (head == NULL)
    return NULL;

  // case for single node
  if (head->next == NULL && n == 0)
  {
    current = head->next;
    free(head);
    return current;
  }

  // base case
  if (n == 0)
  {
    current = head->next;
    free(head);
    current->prev = NULL;
    return current;
  }

  current = head;
  i = 0;

  while ((current->next != NULL) && (i < n - 1))
  {
    current = current->next;
    i++;
  }

  // case for last node
  if (current->next == NULL)
  {
    printf("Moved to far in the list\n");
    return head;
  }

  temp = current->next->next;
  free(current->next);
  current->next = temp;

  // case for last node
  if (temp != NULL)
    temp->prev = current;

  return head;
}

node *deleteAlt(node *head)
{
  node *current, *next;

  // case for single node
  if (head == NULL || head->next == NULL)
    return head;

  current = head;
  next = head->next;

  // case for even or odd length linkedlist
  while (current != NULL || next != NULL)
  {
    current->next = next->next;

    // case for even length list last node
    if (next->next == NULL)
    {
      free(next);
      break;
    }

    next->next->prev = current;
    free(next);
    current = current->next;

    // case for odd length list last node
    if (current != NULL)
      next = current->next;
  }

  return head;
}

node *insert_sorted(node *head, int n)
{
  node *current, *sorted_node;

  // base case
  if (n <= head->data)
  {
    sorted_node = create_node(n);
    sorted_node->next = head;
    head->prev = sorted_node;
    return sorted_node;
  }

  // case for single node
  if ((head->next == NULL) && (n <= head->data))
  {
    sorted_node = create_node(n);
    sorted_node->next = head;
    head->prev = sorted_node;
    return sorted_node;
  }

  current = head;
  while ((current->next != NULL) && (n > current->next->data))
    current = current->next;

  // case for last node
  if (current->next == NULL)
  {
    sorted_node = create_node(n);
    current->next = sorted_node;
    sorted_node->prev = current;
    return head;
  }

  sorted_node = create_node(n);

  sorted_node->prev = current;
  sorted_node->next = current->next;

  current->next->prev = sorted_node;
  current->next = sorted_node;

  return head;
}

int *create_array(int n)
{
  int i;
  int *array;

  if (n == 0)
    return NULL;

  array = malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND_VAL + 1;

  return array;
}

void print_array(int *array, int n)
{
  int i;

  if (array == NULL)
    return;

  for (i = 0; i < n; i++)
    printf("%d ", array[i]);

  printf("\n");
}

int main(void)
{
  int *array, i, len = 9;
  node *head = NULL;
  srand(time(NULL));

  array = create_array(len);
  print_array(array, len);

  for (i = 0; i < len; i++)
    head = head_insert(head, array[i]);

  print_list(head);

  head = tail_insert(head, 12);
  print_list(head);

  head = head_delete(head);
  print_list(head);

  head = tail_delete(head);
  print_list(head);

  head = deleteAlt(head);
  print_list(head);

  head = deleteNth(head, 3);
  print_list(head);

  head = deleteNth(head, 6);
  print_list(head);

  head = tail_delete(head);
  print_list(head);

  head = tail_insert(head, 44);
  print_list(head);

  head = tail_delete(head);
  print_list(head);

  head = tail_insert(head, 44);
  print_list(head);

  head = destroy_list(head);
  free(array);

  return 0;
}
