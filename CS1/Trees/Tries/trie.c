#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 1023

typedef struct TrieNode
{
 int count;
 struct TrieNode *children[26];
} TrieNode;

TrieNode *createNode(void)
{
  int i;
  TrieNode *new_node = malloc(sizeof(TrieNode));

  new_node->count = 0;
  for (i = 0; i < 26; i++)
    new_node->children[26];

  return new_node;
}

// Big-O: Worst-Case: O(k), Best-Case: O(k), Space-Complexity: O(k)
TrieNode *insert(TrieNode *root, char *str)
{
  int i, len, index;
  TrieNode *wizard;

  if (str == NULL)
    return NULL;

  if (root == NULL)
    root = createNode();

  len = strlen(str);
  wizard = root;

  for (i = 0; i < len; i++)
  {
    if (!isalpha(str[i]))
      return NULL;

    index = tolower(str[i]) - 'a';

    if (wizard->children[index] == NULL)
      wizard->children[index] = createNode();

    wizard = wizard->children[index];
  }

  wizard->count++;
  return root;
}

// Big-O: Worst-Case: O(k), Best-Case: O(1), Space-Complexity: O(1)
int containtsWord(TrieNode *root, char *str)
{
  int i, len, index;
  TrieNode *wizard;

  if (root == NULL || str == NULL)
    return 0;

  len = strlen(str);
  wizard = root;

  for (i = 0; i < len; i++)
  {
    if (!isalpha(str[i]))
      return 0;

    index = tolower(str[i]) - 'a';

    if (wizard->children[index] == NULL)
      return 0;

    wizard = wizard->children[index];
  }

  return (wizard->count > 0 ? 1 : 0);
}

// Big-O: Worst-Case: O(k), Best-Case: O(1), Space-Complexity: O(1)
TrieNode *getNode(TrieNode *root, char *str)
{
  int i, len, index;
  TrieNode *wizard;

  if (root == NULL || str == NULL)
    return NULL;

  len = strlen(str);
  wizard = root;

  for (i = 0; i < len; i++)
  {
    if (!isalpha(str[i]))
      return NULL;

    index = tolower(str[i]) - 'a';

    if (wizard->children[index] == NULL)
      return NULL;

    wizard = wizard->children[index];
  }

  return (wizard->count > 0) ? wizard : NULL;
}

TrieNode *destroyTrie(TrieNode *root)
{
  int i;

  for (i = 0; i < 26; i++)
    if (root->children[i] != NULL)
      destroyTrie(root->children[i]);

  free(root);
  return NULL;
}

int countNodes(TrieNode *root)
{
  int i, count;

  if (root == NULL)
    return 0;

  count = 0;
  for (i = 0; i < 26; i++)
    if (root->children[i] != NULL)
      count += countNodes(root->children[i]);

  return 1 + count;
}

void printTrieHelper(TrieNode *root, char *buffer, int k)
{
  int i;

  if (root == NULL || buffer == NULL)
    return;

  if (root->count > 0)
    printf("%s (%d)\n", buffer, root->count);

  buffer[k + 1] = '\0';

  for (i = 0; i < 26; i++)
  {
    buffer[k] = i + 'a';

    if (root->children[i] != NULL)
      printTrieHelper(root->children[i], buffer, k + 1);
  }

  buffer[k] = '\0';
}

void printTrie(TrieNode *root)
{
  char buffer[MAX_WORD_LENGTH + 1];
  buffer[0] = '\0';
  printTrieHelper(root, buffer, 0);
}

void dedupe(char *infile, char *outfile)
{
  char buffer[1024];
  FILE *ifp, *ofp;

  TrieNode *root = createNode();

  if ((ifp = fopen(infile, "r")) == NULL)
  {
    fprintf(stderr, "ERROR: Could not write to file in dedupe(): %s\n", infile);
    fclose(ifp);
    return;
  }

  if ((ofp = fopen(outfile, "w")) == NULL)
  {
    fprintf(stderr, "ERROR: Could not write to file in dedupe(): %s\n", outfile);
    fclose(ofp);
    return;
  }

  while (fscanf(ifp, "%s" ,buffer) != EOF)
  {
    if (containtsWord(root, buffer))
      continue;

    root = insert(root, buffer);
    fprintf(ofp, "%s\n", buffer);
  }

  fclose(ifp);
  fclose(ofp);
  root = destroyTrie(root);
}

TrieNode *buildTrie(char *filename)
{
	TrieNode *root = NULL;
	char buffer[MAX_WORD_LENGTH + 1];

	FILE *ifp;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
		return NULL;
	}

	// Insert strings one-by-one into the trie.
	while (fscanf(ifp, "%s", buffer) != EOF)
		root = insert(root, buffer);

	fclose(ifp);
	return root;
}

int main(void)
{
  TrieNode *root = buildTrie("corpus.txt");
  printTrie(root);
  printf("%d\n", countNodes(root));
  root = destroyTrie(root);
  return 0;
}
