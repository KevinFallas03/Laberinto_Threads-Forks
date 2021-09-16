#include "maze_utils.h"

char *maze_to_str(Maze maze) 
{
    char *str;

    // allocate memory for the maze string representation
    str = (char *) malloc(maze->height * maze->width + maze->height + 1);

    for (int x = 0; x < maze->width; x++)
    {
      for (int y = 0; y < maze->height; y++)
        str[x * maze->width + y] = maze->map[ y ][ x ]; 
    
      str[x * maze->width + maze->height]= x == (maze->width-1) ? '\n' : '\0';
    }

    return str;
}

void free_maze(Maze maze) 
{
  for (int i=0; i<maze->height; i++)
    free(maze->map[i]);

  free(maze);
}
