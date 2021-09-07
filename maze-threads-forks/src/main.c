#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "maze-loader/loader.c"

Maze original_maze = NULL;

#include "maze-solver/solver.c"


int main() {
    srand(time(NULL));
    original_maze = load_maze("../utils/lab1.txt");
    original_maze->map[0][0] = 1;
    original_maze->map[1][0] = 1;
    original_maze->map[2][0] = 1;
    original_maze->map[2][1] = 2;
    original_maze->map[2][2] = 2;
    original_maze->map[1][2] = 3;
    original_maze->map[0][2] = 3;
    original_maze->map[0][3] = 4;
    original_maze->map[0][4] = 4;
    print_maze(original_maze);
    // create_thread('s',0,0,0);
    return 0;
}

