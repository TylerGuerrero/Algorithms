// maze.c
// ======
// This program reads an ASCII maze from an input file and uses backtracking to
// help guide a person (signified by a '@' symbol) to the maze's exit (signified
// by the 'e' symbol).

// Anatomy of a BackTracking Solution
// 1) Base Case
// 2) (Optional) Check for duplicate state
// 3) Generate Possible Move
// 3a) Check validity of move
// 3b) Change State
// 3c) Perform Recursive Descent
// 3d) (Optional) Process return value of Recursive Call
// 3e) Undo State Change

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Number of seconds to wait between calls to print_maze(). This affects how
// fast the "animation" effect works.
#define DEFAULT_WAIT_TIME 0.5

// Do nothing for wait_time_in_seconds number of seconds.
void wait(double wait_time_in_seconds)
{
	clock_t start_ticks, end_ticks;

	start_ticks = clock();
	end_ticks = start_ticks + CLOCKS_PER_SEC * wait_time_in_seconds;

	while (clock() < end_ticks);
}


// Read an ASCII maze from a file. See the attached files for the expected
// format. The recognized characters are:

//   '@' - person (there should be exactly one of these per maze)
//   '#' - wall
//   ' ' - a space where the person can walk
//   'e' - exit (there can be multiple exits or none at all)

// This function returns 0 if it fails to open the input file or if it fails to
// find the '@' symbol in the maze. Otherwise, it returns 1 to indicate that
// the maze was read successfully. It doesn't have a lot of error checking.
int read_maze(char *filename, char ***maze, int *height, int *width,
              int *start_i, int *start_j)
{
	int i, j;
	FILE *ifp = fopen(filename, "r");

	// Initialize starting coordinates to something invalid. If these don't get
	// updated before the function terminates, we know we failed to find our
	// person ('@') in the maze.
	*start_i = *start_j = -1;

	if (ifp == NULL)
		return 0;

	// The input file starts with the height and width of the maze.
	fscanf(ifp, "%d %d", height, width);

	// Allocate space for the 2D maze. Because 'maze' is a pointer to the
	// (char **) that we declared in main(), we have to dereference it to go to
	// that (char **), and then we can create (and access) the array we need
	// here.
	*maze = malloc(sizeof(char *) * *height);
	for (i = 0; i < *height; i++)
		(*maze)[i] = malloc(sizeof(char) * *width);

	// Read the maze from the text file.
	for (i = 0; i < *height; i++)
	{
		for (j = 0; j < *width; j++)
		{
			fscanf(ifp, "%c", &((*maze)[i][j]));

			// If we encounter end-of-line characters, move on to the next
			// character. We can't use our " %c" trick with scanf() to ignore all
			// whitespace characters, because there are ' ' characters in the input
			// file that we do want to read.

			// The inclusion of '\r' here is to make this program Windows friendly,
			// but I haven't tested it on Windows. I hope it works. :)
			while (((*maze)[i][j] == '\n') || ((*maze)[i][j] == '\r'))
				fscanf(ifp, "%c", &((*maze)[i][j]));

			// Keep track of the location of the '@' character in the maze.
			if ((*maze)[i][j] == '@')
			{
				*start_i = i;
				*start_j = j;
			}
		}
	}

	fclose(ifp);

	// If we failed to find the '@' character, return 0 to indicate failure.
	if (*start_i == -1)
		return 0;

	return 1;
}

void print_maze(char **maze, int height, int width, int searching)
{
  int i, j;

  if (maze == NULL)
    return;

  printf("\n");
  if (searching == 1)
    printf("Searching...\n");
  else if (searching == 2)
    printf("Exit Found ...\n");
  else
    printf("BackTracking...\n");

  for (i = 0; i < height; i++)
    for (j = 0; j < width; j++)
      printf("%c%s", maze[i][j], (j == width - 1) ? "\n" : "");
}

char **destroy_maze(char **maze, int height, int width)
{
  int i;

  if (maze == NULL)
    return NULL;

  for (i = 0; i < height; i++)
    free(maze[i]);

  free(maze);
  return NULL;
}

int in_bounds(int height, int width, int i, int j)
{
  return ((i >= 0) && (i < height) && (j >= 0) && (j < width));
}

char **make_visited_array(char **maze, int height, int width)
{
  int i, j;
  char **visited;

  if (maze == NULL)
    return NULL;

  visited = malloc(sizeof(char*) * height);
  for (i = 0; i < height; i++)
    visited[i] = malloc(sizeof(char) * width);

  for (i = 0; i < height; i++)
    for (j = 0; j < width; j++)
      visited[i][j] = ((maze[i][j] == '#') || (maze[i][j] == '@')) ? 1 : 0;

  return visited;
}

// A function to flash a '*' symbol when the person ('@') reaches the exit ('e').
void win(char **maze, int height, int width, int i, int j, double wait_time_in_seconds)
{
	maze[i][j] = '*';
	print_maze(maze, height, width, 2);
	wait(wait_time_in_seconds);

	maze[i][j] = '@';
	print_maze(maze, height, width, 2);
	wait(wait_time_in_seconds);

	maze[i][j] = '*';
	print_maze(maze, height, width, 2);
	wait(wait_time_in_seconds);

	maze[i][j] = 'e';
	print_maze(maze, height, width, 2);
	wait(wait_time_in_seconds);
}

int maze_runner(char **maze, char **visited, int height, int width, int i, int j, double wait_time_in_seconds)
{
  int m, new_i, new_j;
  char breadcrumb = '.';

  if (maze == NULL || visited == NULL)
    return 0;

  // (row, col)
  int moves[4][2] = { {1, 0},
                      {-1, 0},
                      {0, 1},
                      {0, -1}};

  print_maze(maze, height, width, 1);
  wait(wait_time_in_seconds);

  // base case
  if (visited[i][j] == 'e')
  {
    win(maze, height, width, i, j, wait_time_in_seconds);
    return 1;
  }

  // Generate Possible Moves
  for (m = 0; m < 4; m++)
  {
    new_i = i + moves[m][0];
    new_j = j + moves[m][1];

    if (!in_bounds(height, width, new_i, new_j))
      continue;

    // Check validity of move
    if (visited[new_i][new_j] == 1)
      continue;

    // Check validity of move
    // have to do this casue you will over write
    // the 'e' in the maze 2-d array
    if (maze[new_i][new_j] == 'e')
      visited[new_i][new_j] = 'e';
    else
      visited[new_i][new_j] = 1;

    // Change state
    maze[i][j] = breadcrumb;
    maze[new_i][new_j] = '@';

    // Perform Recursive Descent and
    // Process return value of Recursive Call
    if (maze_runner(maze, visited, height, width, new_i, new_j, wait_time_in_seconds))
      return 1;

    // undo state change
    maze[new_i][new_j] = breadcrumb;
    maze[i][j] = '@';

    print_maze(maze, height, width, 0);
    wait(wait_time_in_seconds);
  }

  return 0;
}

int main(int argc, char **argv)
{
	int height, width, start_i, start_j;
	char **maze = NULL, **visited = NULL;
	double wait_time;

	// You must provide the name of an input file at the command line.
	if (argc < 2)
	{
		printf("Proper syntax: %s <filename>\n", argv[0]);
		return 1;
	}

	// Attempt to read maze from input file.
	if (!read_maze(argv[1], &maze, &height, &width, &start_i, &start_j))
	{
		printf("Failed to read maze from file: %s\n", argv[1]);
		return 1;
	}

	wait_time = (argc < 3) ? DEFAULT_WAIT_TIME : atof(argv[2]);

	// Create 'visited' array and kick off backtracking.
	visited = make_visited_array(maze, height, width);
	maze_runner(maze, visited, height, width, start_i, start_j, wait_time);

	// Memory management.
	maze = destroy_maze(maze, height, width);
	visited = destroy_maze(visited, height, width);

	return 0;
}
