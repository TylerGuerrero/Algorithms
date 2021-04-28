#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HOORAY 0
#define OH_NOOO 1

typedef struct node
{
  int data;
  struct node *left, *right;
} node;

node *create_node(int data)
{
  node *new_node = malloc(sizeof(node));
  new_node->data = data;
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}

node *BST_insert(node *root, int data)
{
  if (root == NULL)
    return create_node(data);
  else if (data < root->data)
    root->left = BST_insert(root->left, data);
  else if (data > root->data)
    root->right = BST_insert(root->right, data);
  else
    ;

  return root;
}

int BST_search(node *root, int data)
{
  if (root == NULL)
    return 0;
  else if (data < root->data)
    return BST_search(root->left, data);
  else if (data > root->data)
    return BST_search(root->right, data);
  else
    return 1;
}

int BST_search_iterative(node *root, int data)
{
  if (root == NULL)
    return 0;

  while (root != NULL)
  {
    if (data < root->data)
      root = root->left;
    else if (data > root->data)
      root = root->right;
    else
      return 1;
  }

  return 0;
}

int find_max_recursive(node *root)
{
  if (root == NULL)
    return INT_MIN;
  else if (root->right == NULL)
    return root->data;
  else
    return find_max_recursive(root->right);
}

int find_max_iterative(node *root)
{
  if (root == NULL)
    return INT_MIN;

  while (root->right != NULL)
    root = root->right;

  return root->data;
}

node *BST_delete(node *root, int data)
{
  node *temp;

  if (root == NULL)
    return NULL;
  else if (data < root->data)
    root = BST_delete(root->left, data);
  else if (data > root->data)
    root = BST_delete(root->right, data);
  else
  {
    if (root->right == NULL && root->left == NULL)
    {
      free(root);
      root = NULL;
    }
    else if (root->left != NULL && root->right == NULL)
    {
      temp = root->left;
      free(root);
      root = temp;
    }
    else if (root->right != NULL && root->left == NULL)
    {
      temp = root->right;
      free(root);
      root = temp;
    }
    else
    {
      root->data = find_max_recursive(root->left);
      root->left = BST_delete(root->left, root->data);
    }
  }

  return root;
}

void inorder_traversal_helper(node *root)
{
  if (root == NULL)
    return;

  inorder_traversal_helper(root->left);
  printf("%d ", root->data);
  inorder_traversal_helper(root->right);
}

void inorder_traversal(node *root)
{
  if (root == NULL)
  {
    printf("Empty Tree\n");
    return;
  }

  inorder_traversal_helper(root);
}

void preorder_traversal_helper(node *root)
{
  if (root == NULL)
    return;

  printf("%d ", root->data);
  preorder_traversal_helper(root->left);
  preorder_traversal_helper(root->right);
}

void preorder_traversal(node *root)
{
  if (root == NULL)
  {
    printf("Empty Tree\n");
    return;
  }

  preorder_traversal_helper(root);
}

void postorder_traversal_helper(node *root)
{
  if (root == NULL)
    return;

  postorder_traversal_helper(root->left);
  postorder_traversal_helper(root->right);
  printf("%d ", root->data);
}

void postorder_traversal(node *root)
{
  if (root == NULL)
  {
    printf("Empty Tree\n");
    return;
  }

  postorder_traversal_helper(root);
}

node *forest_fire(node *root)
{
  if (root == NULL)
    return NULL;

  forest_fire(root->left);
  forest_fire(root->right);
  free(root);
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int count_node(node *root)
{
  if (root == NULL)
    return 0;

  return 1 + count_node(root->left) + count_node(root->right);
}

int count_node_condensed(node *root)
{
  return (root == NULL) ? 0 : 1 + count_node_condensed(root->left) + count_node_condensed(root->right);
}

int count_even_nodes(node *root)
{
  if (root == NULL)
    return 0;

  return (root->data % 2 == 0) + count_even_nodes(root->left) + count_even_nodes(root->right);
}

int count_values(node *root)
{
  if (root == NULL)
    return 0;

  return root->data + count_values(root->left) + count_values(root->right);
}

int height(node *root)
{
  if (root == NULL)
    return -1;

  return 1 + max(height(root->left), height(root->right));
}

int height_excessively_fancy(node *root)
{
  return (root == NULL) ? -1 : 1 + height_excessively_fancy(root->left) + height_excessively_fancy(root->right);
}
