#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
  int data;
  struct node *next;
} node;

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

node *tail_insert(node *head, int data)
{
  node *current;

  if (head == NULL)
    return create_node(data);

  for (current = head; current->next != NULL; current = current->next);

  current->next = create_node(data);
  return head;
}

node *tail_insert_alternative(node *head, int data)
{
  node *current;

  if (head == NULL)
    return create_node(data);

  current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = create_node(data);
  return head;
}

node *recursive_tail_insert(node *head, int data)
{
  if (head == NULL)
    return create_node(data);

  head->next = recursive_tail_insert(head->next, data);
  return head;
}

node *fast_tail_insert(node *tail, int data)
{
  if (tail == NULL)
    return create_node(data);

  tail->next = create_node(data);
  tail = tail->next;
  return tail;
}

node *head_insert(node *head, int data)
{
  node *new_head;

  if (head == NULL)
    return create_node(data);

  new_head = create_node(data);
  new_head->next = head;
  return new_head;
}

void headInsert(node **head, int data)
{
  node *new_head;

  if (*head == NULL)
  {
    *head = create_node(data);
    return;
  }

  new_head = create_node(data);
  new_head->next = *head;
  *head = new_head;
}

node *destroy_linked_list(node *head)
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

node *recursive_destroy_linked_list(node *head)
{
  if (head == NULL)
    return NULL;

  recursive_destroy_linked_list(head->next);
  printf("Destroying node with value %d\n", head->data);
  free(head);
  return NULL;
}

node *alternative_recursive_destroy_linked_list(node *head)
{
  node *temp;

  if (head == NULL)
    return NULL;

  temp = head->next;
  free(head);
  alternative_recursive_destroy_linked_list(temp);
  return NULL;
}

void print_list(node *head)
{
  node *current;

  if (head == NULL)
    return;

  for (current = head; current != NULL; current = current->next)
    printf("%d%c", current->data, ((current->next == NULL) ? '\n' : ' '));
}

void print_list_alternative(node *head)
{
  if (head == NULL)
    return;

  for (head = head; head != NULL; head = head->next)
    printf("%d%c", head->data, ((head->next != NULL) ? ' ' : '\n'));
}

void print_list_fancy(node *head)
{
  if (head == NULL)
    return;

  for ( ; ; )
  {
    if (head == NULL)
      break;

    printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
    head = head->next;
  }
}

void print_list_recursive_helper(node *head)
{
  if (head == NULL)
    return;

  printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
  print_list_recursive_helper(head->next);
}

void print_list_recursive(node *head)
{
  if (head == NULL)
  {
    printf("Empty List\n");
    return;
  }

  print_list_recursive_helper(head);
}

void reverse_print_list_helper(node *head)
{
  if (head == NULL)
    return;

  reverse_print_list_helper(head->next);
  printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
}

void reverse_print_list(node *head)
{
  if (head == NULL)
  {
    printf("Empty List\n");
    return;
  }

  reverse_print_list_helper(head);
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
    free(head);
    return NULL;
  }

  // case for first node
  if (n == 0)
  {
    current = head->next;
    free(head);
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
    printf("Went to far in the list\n");
    return head;
  }

  temp = current->next->next;
  free(current->next);
  current->next = temp;
  return head;
}

node *deleteNthRecursive(node *head, int n)
{
  node *current;

  if (head == NULL)
    return NULL;

  if (n == 0)
  {
    current = head->next;
    free(head);
    return current;
  }

  head->next = deleteNthRecursive(head->next, n - 1);
  return head;
}

node *deleteAlt(node *head)
{
  node *current, *next;

  // case for single node
  if (head == NULL  || head->next == NULL)
    return head;

  current = head;
  next = head->next;

  // case for even or odd length linked list
  while (current != NULL && next != NULL)
  {
    current->next = next->next;
    free(next);
    current = current->next;

    // case for last node
    if (current != NULL)
      next = current->next;
  }

  return head;
}

node *deleteAltRecursive(node *head)
{
  node *next;

  if (head == NULL || head->next == NULL)
    return head;

  next = head->next;
  head->next = next->next;
  free(next);
  deleteAltRecursive(head->next);
  return head;
}

node *insertSortedNode(node *head, int n)
{
  node *current, *sorted_node;

  if (head == NULL)
    return create_node(n);

  // case for first node
  if (n <= head->data)
  {
    sorted_node = create_node(n);
    sorted_node->next = head;
    return sorted_node;
  }

  current = head;
  while ((current->next != NULL) && (n > current->next->data))
    current = current->next;

  // case for last node
  if (current->next == NULL)
  {
    current->next = create_node(n);
    return head;
  }

  sorted_node = create_node(n);
  sorted_node->next = current->next;
  current->next = sorted_node;
  return head;
}
