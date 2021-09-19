#include "memo.h"

Maze create_shared_maze(Dimension dim) 
{   
    // allocate enough memory for the maze map
    Maze maze = 
        (Maze) 
        mmap( 
            NULL,
            sizeof(struct maze),
            PROT_READ  | PROT_WRITE, // protection flags
            MAP_SHARED | MAP_ANONYMOUS, // visibility flags
            0, 
            0
        );

    maze->map = (char**) mmap( 
            NULL,
            sizeof(char*) * dim->height,
            PROT_READ  | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,
            0, 
            0
        );

    for (int i=0; i< dim->height; i++)
        maze->map[i] = (char*) malloc(sizeof(char) * dim->width);

    return maze;
}

Maze create_maze(Dimension dim) 
{
    Maze maze = (Maze) malloc(sizeof(struct maze));
    
    // allocate enough memory for the maze map
    maze->map = (char**) malloc(sizeof(char*) * dim->height);
    for (int i=0; i<dim->height; i++)
        maze->map[i] = (char*) malloc(sizeof(char) * dim->width);

    return maze;
}


