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

#define ROW_FINISH_MARK 10

#define MATRIX_MODE 0
#define DIMENSION_MODE 1

#define THREADS_MODE 0
#define FORKS_MODE 1

int get_dimensions(Dimension dim, char* filename);
Maze load_maze(char *filename, int strategy_mode);
void show_maze(Maze maze);