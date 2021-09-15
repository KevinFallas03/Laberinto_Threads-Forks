#ifndef FILE
    #include<stdio.h>
#endif

#ifndef free
    #include<stdlib.h>
#endif

#ifndef isdigit
    #include<ctype.h>
#endif

#define __LOADER__ 

typedef struct maze {
    int width;
    int height;
    char **map;
}* Maze;

#define ROW_FINISH_MARK 10

#define MATRIX_MODE 0
#define DIMENSION_MODE 1

int get_dimensions(Maze maze, char* filename);
Maze load_maze(char *filename);
void show_maze(Maze maze);