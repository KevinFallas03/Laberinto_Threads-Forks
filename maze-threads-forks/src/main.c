#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "maze-loader/loader.c"

Maze original_maze = NULL;
int winners = 0;

#include "maze-solver/solver.c"

void run_solver_with_threads(char *filename);


int main() {
    srand(time(NULL));
    run_solver_with_threads("../utils/lab1.txt");
}

void manual_test() {
    original_maze->map[0][0] = 1;
    print_maze(original_maze);
    original_maze->map[1][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][1] = 2;
    print_maze(original_maze);
    original_maze->map[2][2] = 2;
    print_maze(original_maze);
    original_maze->map[1][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][3] = 4;
    print_maze(original_maze);
    original_maze->map[0][4] = 4;
    print_maze(original_maze); 
}

void run_solver_with_threads(char *filename) 
{
    original_maze = load_maze(filename);
    
    solve_with_threads(
        DOWN, // direction (DOWN by default)
        0,    // initial x position
        0,    // initial y position
        0,    // current x position
        0,    // current y position
        0     // initial steps amount
    );

    // solve_with_forks(
    //     DOWN, // direction (DOWN by default)
    //     0,    // initial x position
    //     0,    // initial y position
    //     0,    // current x position
    //     0,    // current y position
    //     0     // initial steps amount
    // );

    show_stats();
}
