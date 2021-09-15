#ifndef __WALKER_DEFINITION__
    #include "../solver/solver.h"
#endif

#ifndef __LOADER__
    #include "../loader/loader.c"
#endif

Walker build_walker(char direction, int start_row, int start_col, int current_row, int current_column, int steps);
Maze copy_maze(Maze original);