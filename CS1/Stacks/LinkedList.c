#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

node *create_node (int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
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

node *head_delete(node *head)
{
  node *new_head;

  if (head == NULL)
    return NULL;

  new_head = head->next;
  free(head);
  return new_head;
}

void print_list(node *head)
{
  if (head == NULL)
    return;

  printf("%d%c", head->data,((head->next == NULL) ? '\n' : ' '));
  print_list(head->next);
}

node *destroy_linked_list(node *head)
{
  if (head == NULL)
    return NULL;

  destroy_linked_list(head->next);
  free(head);
  return NULL;
}
