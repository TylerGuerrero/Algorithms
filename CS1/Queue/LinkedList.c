#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
  new_node->data = data;
  return new_node;
}

void print_list(node *head)
{
  if (head == NULL)
    return;

  printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
  print_list(head->next);
}

node *destroy_list(node *head)
{
  if (head == NULL)
    return NULL;

  destroy_list(head->next);
  free(head);
  return NULL;
}

LinkedList *create_list(void)
{
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

LinkedList *destroy_linked_list(LinkedList *list)
{
  if (list == NULL)
    return NULL;
  else if (list->head == NULL && list->tail == NULL)
  {
    free(list);
    return NULL;
  }
  else
  {
    list->head = list->tail = destroy_list(list->head);
    free(list);
    return NULL;
  }
}

void tail_insert(LinkedList *list, int data)
{
  if (list == NULL)
    return;
  else if (list->tail == NULL)
    list->head = list->tail = create_node(data);
  else
  {
    list->tail->next = create_node(data);
    list->tail = list->tail->next;
  }
}

void head_delete(LinkedList *list)
{
  node *new_head;

  if (list == NULL)
    return;
  else if (list->head == NULL)
  {
    free(list);
    return;
  }
  else
  {
    new_head = list->head->next;
    free(list->head);
    list->head = new_head;

    if (list->head == NULL)
      list->tail = NULL;
  }
}

void print_linked_list(LinkedList *list)
{
  if (list == NULL)
  {
    printf("Empty List\n");
    return;
  }

  print_list(list->head);
}
