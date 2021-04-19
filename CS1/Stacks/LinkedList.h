#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

typedef struct node
{
  int data;
  struct node *next;
} node;

node *create_node(int data);

node *head_insert(node *head, int data);

void headInsert(node **head, int data);

node *head_delete(node *head);

node *destroy_linked_list(node *head);

void print_list(node *head);

#endif
