#include "timer.h"

void eval_solver
(
    void (*solve)(char,int,int,int,int,int), 
    char *strategy_name,
    char *filename,
    int strategy_mode
)
{
    
    // load maze from file
    original_maze = load_maze(filename, strategy_mode);

    // set start time
    clock_t begin = clock();

    // call the maze solve function, with function as param
    solve(
        DEFAULT_START_DIRECTION, 
        0, 
        0, 
        0, 
        0, 
        0
    );

    // finish taking the time
    clock_t end = clock();

    // convert cloc ticks to seconds
    double time_spent = (double)(end - begin) / (double) (CLOCKS_PER_SEC);

    // show results
    printf("\n[%s] -> %3.5f seconds", strategy_name, time_spent);
}