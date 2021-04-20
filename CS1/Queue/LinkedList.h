#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

// Type Defentions
typedef struct node
{
  int data;
  struct node *next;
} node;

typedef struct LinkedList
{
  node *head;
  node *tail;
} LinkedList;

// Function Defentions
node *create_node(int data);

void print_list(node *head);

node *destroy_list(node *head);

LinkedList *create_list(void);

LinkedList *destroy_linked_list(LinkedList *list);

void tail_insert(LinkedList *list, int data);

void head_delete(LinkedList *list);

void print_linked_list(LinkedList *list);

#endif
