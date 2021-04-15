#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// circular linked list with head and tail pointers

typedef struct node
{
  int data;
  struct node *next;
} node;

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
  new_node->data = data;
  return new_node;
}

void ouroboros_head_insert_fancy(node **head, node **tail, int data)
{
  node *new_head;

  if (*head == NULL || *tail == NULL)
  {
    *head = *tail = create_node(data);
    (*head)->next = *head;
    return;
  }
  else
  {
    new_head = create_node(data);
    new_head->next = *head;
    *head = new_head;
    (*tail)->next = *head;
  }
}

void ouroboros_head_delete_fancy(node **head, node **tail)
{
  node *new_head;

  if (*head == NULL || *tail == NULL)
    return;
  // case for single node
  else if ((*head)->next == *head)
  {
    free(*head);
    *head = *tail = NULL;
    return;
  }
  else
  {
    new_head = (*head)->next;
    free(*head);
    *head = new_head;
    (*tail)->next = *head;
  }
}

void ouroboros_tail_insert_fancy(node **head, node **tail, int data)
{
  if (*head == NULL || *tail == NULL)
  {
    *head = *tail = create_node(data);
    (*head)->next = *head;
    return;
  }
  else
  {
    (*tail)->next = create_node(data);
    *tail = (*tail)->next;
    (*tail)->next = *head;
  }
}

void ouroboros_tail_delete_fancy(node **head, node **tail)
{
  node *current;

  if (*head == NULL || *tail == NULL)
    return;
  // case for single node
  else if ((*head)->next == *head)
  {
    free(*head);
    *head = *tail = NULL;
    return;
  }
  else
  {
    current = *head;
    while (current->next != *tail)
      current = current->next;

    free(current->next);
    *tail = current;
    (*tail)->next = *head;
  }
}

node *free_circular_list(node *head)
{
  node *current, *temp;

  if (head == NULL)
    return NULL;

  current = head;
  do
  {
    temp = current->next;
    free(current);
    current = temp;
  } while (current != head);

  return NULL;
}

void print_circular_list(node *head)
{
  node *current;

  if (head == NULL)
    return;

  printf("%d%c", head->data, ((head->next == head) ? '\n' : ' '));

  for (current = head->next; current != head; current = current->next)
    printf("%d%c", current->data, ((current->next == head) ? '\n' : ' '));
}

void do_print_circular_list(node *head)
{
  node *current;

  if (head == NULL)
    return;

  current = head;
  do
  {
    printf("%d%c", current->data, ((current->next == head) ? '\n' : ' '));
    current = current->next;
  } while (current != head);
}

void clever_print_circular_list(node *head)
{
  node *current;

  if (head == NULL)
    return;

  current = head;
  while (current != NULL)
  {
    printf("%d%c", current->data, ((current->next == head) ? '\n' : ' '));
    current = current->next;

    if (current == head)
      current = NULL;
  }
}

void clever_print_circular_list_alternate(node *head)
{
  node *current;

  if (head == NULL)
    return;

  current = head;
  while (1)
  {
    printf("%d%c", current->data, ((current->next == head) ? '\n' : ' '));
    current = current->next;

    if (current == head)
      break;
  }
}

void deleteNth(node **head, node **tail, int n)
{
  node *current, *temp;
  int i;

  if (*head == NULL || *tail == NULL)
    return;
  // case for single node
  else if ((*head)->next == *head && n == 0)
  {
    free(*head);
    *head = *tail = NULL;
    return;
  }
  else if (n == 0)
  {

  }
  else
  {
    current = *head;
    i = 0;

    while ((current->next != *head) && (i < n - 1))
    {
      current = current->next;
      i++;
    }

    // case for last node
    if (current->next == *head)
    {
      printf("Went to far in the list\n");
      return;
    }

    // case for last node
    if (current->next->next == *head)
    {
      free(current->next);
      *tail = current;
      (*tail)->next = *head;
      return;
    }

    temp = current->next->next;
    free(current->next);
    current->next = temp;
  }
}

void deleteAlt(node **head)
{
  node *current, *next;

  // case for single node
  if (*head == NULL || (*head)->next == *head)
    return;

  current = *head;
  next = (*head)->next;

  while (1)
  {
    current->next = next->next;
    free(next);
    current = current->next;

    // case for last node
    if (current != *head)
      next = current->next;

    // case for even or odd length linked list
    if (current == *head || next == *head)
      break;
  }
}

void ourobors_insert_sorted(node **head, node **tail, int n)
{
  node *current, *sorted_node;

  if (*head == NULL || *tail == NULL)
  {
    *head = *tail = create_node(n);
    (*head)->next = *head;
    return;
  }
  // case for first node
  else if (n <= (*head)->data)
  {
    sorted_node = create_node(n);
    sorted_node->next = *head;
    *head = sorted_node;
    (*tail)->next = *head;
    return;
  }
  else
  {
    current = *head;
    while (current->next != *head && n > current->next->data)
      current = current->next;

    // case for last node
    if (current->next == *head)
    {
      current->next = create_node(n);
      *tail = current->next;
      (*tail)->next = *head;
    }

    sorted_node = create_node(n);
    sorted_node->next = current->next;
    current->next = sorted_node;
  }
}

int main(void)
{
  int array[] = {15, 24, 7, 1, 32, 13, 56, 8, 41, 10}, n = 10, i;
	node *head = NULL, *tail = NULL;

	for (i = 0; i < n; i++)
		ouroboros_head_insert_fancy(&head, &tail, array[i]);

	print_circular_list(head);
	do_print_circular_list(head);
	clever_print_circular_list(head);
	clever_print_circular_list_alternate(head);
  ouroboros_tail_insert_fancy(&head, &tail, 77);
  print_circular_list(head);
  ouroboros_head_delete_fancy(&head, &tail);
  print_circular_list(head);
  ouroboros_tail_delete_fancy(&head, &tail);
  print_circular_list(head);

  deleteNth(&head, &tail, 3);
  print_circular_list(head);
  ouroboros_head_insert_fancy(&head, &tail, 3);
  print_circular_list(head);
  deleteNth(&head, &tail, 8);
  print_circular_list(head);

  ouroboros_tail_insert_fancy(&head, &tail, 13);
  ouroboros_tail_insert_fancy(&head, &tail, 12);
  //  ouroboros_tail_insert_fancy(&head, &tail, 88);
  print_circular_list(head);

  deleteAlt(&head);
  print_circular_list(head);

  head = free_circular_list(head);
  return 0;
}
