#ifndef size_t
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define __MEMO__

typedef struct maze {
    int width;
    int height;
    char **map;
}* Maze;

typedef struct dimension {
    int width;
    int height;
}* Dimension;

#include <sys/mman.h>

Maze create_shared_maze(Dimension dim);
Maze create_maze(Dimension dim);