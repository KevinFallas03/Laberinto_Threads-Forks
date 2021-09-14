#ifndef __WALKER_DEFINITION__
    #include "solver.h"
#endif

#ifndef __LOADER__
    #include "loader.h"
#endif

Walker build_walker(char direction, int start_row, int start_col, int current_row, int current_column, int steps)
{
    // set the initial properties
    Walker current_walker = (walker_unit *) malloc(sizeof(walker_unit));

    current_walker->direction = direction;
    current_walker->start_row = start_row;
    current_walker->start_col = start_col;
    current_walker->current_row = current_row;
    current_walker->current_col = current_column;
    current_walker->steps = steps;
    current_walker->color = rand() % COLORS_AMOUNT;

    return current_walker;
}

Maze copy_maze(Maze original) 
{
    Maze copy = (Maze) malloc(sizeof(Maze));

    copy->height = original->height;
    copy->width = original->height;

    copy->map = (char**) malloc(sizeof(char*) * copy->height);
    
    for (int i=0; i<copy->height; i++)
        copy->map[i] = (char*) malloc(sizeof(char) * copy->width);

    for (int i=0; i<copy->height; i++)
        for (int j=0; j<copy->width; j++)
            copy->map[i][j] = original->map[i][j];
          
    return copy;
}

#define ReadEnd  0
#define WriteEnd 1

void send_maze(Maze maze, int* pipeFDs){
    Maze* msg = maze;

    close(pipeFDs[ReadEnd]);                          /* parent writes, doesn't read */

    write(pipeFDs[WriteEnd], msg, sizeof(msg));       /* write the bytes to the pipe */
    close(pipeFDs[WriteEnd]);                         /* done writing: generate eof */
}
void receive_maze(int* pipeFDs){
    Maze* buf;
    close(pipeFDs[WriteEnd]);                         /* child reads, doesn't write */

    while (read(pipeFDs[ReadEnd], &buf, sizeof(buf)) > 0)       /* read until end of byte stream */
      write(STDOUT_FILENO, &buf, sizeof(buf));        /* echo to the standard output */

    close(pipeFDs[ReadEnd]);

}

