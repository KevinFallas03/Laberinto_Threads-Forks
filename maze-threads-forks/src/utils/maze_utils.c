#include "maze_utils.h"

void maze_to_str(Maze maze, char* str) 
{
    int offset = 1;
    str[0] = '\n';
    for (int x = 0; x < maze->height; x++)
    {
      for (int y = 0; y < maze->width; y++) {
        str[x * maze->width + y + offset] = 
          maze->map[ x ][ y ] < COLORS_AMOUNT 
            ? maze->map[ x ][ y ] + '0' 
            : maze->map[ x ][ y ] ; 
      }
    
      str[x * maze->width + maze->height + offset] = 
        x < (maze->width-1) 
          ? '\n' 
          : '\0';
      
      offset++;
    }

}

void free_maze(Maze maze) 
{
  for (int i=0; i<maze->height; i++)
    free(maze->map[i]);

  free(maze->map);
  free(maze);
}
