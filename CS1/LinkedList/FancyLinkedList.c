#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// LinkedList with a head and tail pointer

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

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->next = NULL;
  new_node->data = data;
  return new_node;
}

LinkedList *create_list()
{
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void tail_insert(LinkedList *list, int data)
{
  if (list == NULL)
    return;
  else if (list->tail == NULL && list->head == NULL)
    list->head = list->tail = create_node(data);
  else
  {
    list->tail->next = create_node(data);
    list->tail = list->tail->next;
  }
}

void head_insert(LinkedList *list, int data)
{
  node *new_head;

  if (list == NULL)
    return;
  else if (list->head == NULL && list->tail == NULL)
    list->head = list->tail = create_node(data);
  else
  {
    new_head = create_node(data);
    new_head->next = list->head;
    list->head = new_head;
  }
}

void delete_head(LinkedList *list)
{
  node *new_head;

  if (list == NULL || list->head == NULL)
    return;

  new_head = list->head->next;
  free(list->head);
  list->head = new_head;

  // case for single node
  if (list->head == NULL)
    list->tail = NULL;
}

void tail_delete(LinkedList *list)
{
  node *current;

  if (list == NULL || list->tail == NULL)
    return;
  // case for single node
  else if (list->head->next == NULL)
  {
    free(list->head);
    list->head = list->tail = NULL;
  }
  else
  {
    current = list->head;
    while (current->next != list->tail)
      current = current->next;

    free(list->tail);
    list->tail = current;
    list->tail->next = NULL;
  }
}

void print_list(node *head)
{
  if (head == NULL)
    return;

  printf("%d%c", head->data, ((head->next == NULL) ? '\n' : ' '));
  print_list(head->next);
}

void print_linked_list(LinkedList *list)
{
  if (list == NULL || list->head == NULL)
  {
    printf("Empty List\n");
    return;
  }

  print_list(list->head);
}

node *delete_list(node *head)
{
  if (head == NULL)
    return NULL;

  delete_list(head->next);
  free(head);
  return NULL;
}

LinkedList *destroy_linked_list(LinkedList *list)
{
  if (list == NULL)
    return NULL;
  else if (list->head == NULL || list->tail == NULL)
  {
    free(list);
    return NULL;
  }
  else
  {
    list->head = list->tail = delete_list(list->head);
    free(list);
    return NULL;
  }
}


int main(int argc, char **argv)
{
	LinkedList *list = create_list();

	int i, r, n;

	if (argc < 2)
	{
		// Avoid fringe memory leak. This is pedantic.
		free(list);

		printf("The proper syntax for running this program is: %s <n>\n", argv[0]);
		return 1;
	}

	// Read command line argument.
	n = atoi(argv[1]);

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
		// Notice how much easier it is to call our insertion function now. We
		// don't need to worry about remembering to capture its return value!
		printf("Inserting %d...\n", r = rand() % 100 + 1);
		tail_insert(list, r);
	}

  print_linked_list(list);

  tail_delete(list);
  tail_delete(list);
  print_linked_list(list);

  head_insert(list, 5);
  head_insert(list, 77);
	print_linked_list(list);

  delete_head(list);
  print_linked_list(list);

	// Clean up after yourself.
	list = destroy_linked_list(list);

	return 0;
}
