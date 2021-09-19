#include "timer.h"

void eval_solver
( 
    char *filename,
    int strategy_mode
)
{
    char *strategy_name = strategy_mode == THREADS_STRATEGY ? "THREADS" : "FORKS";

    // load maze from file
    original_maze = load_maze(filename, strategy_mode);

    // set start time
    clock_t begin = clock();

    // call the maze solve function
    switch(strategy_mode)
    {
        case THREADS_STRATEGY:
            solve_with_threads(
                DEFAULT_START_DIRECTION, 
                0, 
                0, 
                0, 
                0, 
                0,
                WAIT
            );
        break;

        case FORKS_STRATEGY:
            solve_with_forks(
                DEFAULT_START_DIRECTION, 
                0, 
                0, 
                0, 
                0, 
                0,
                WAIT
            );
        break;

        default:
            printf("Unknown strategy mode");
    }

    // finish taking the time
    clock_t end = clock();

    // convert cloc ticks to seconds
    double time_spent = (double)(end - begin) / (double) (CLOCKS_PER_SEC);

    // show results
    printf("\n[%s] -> %3.5f seconds", strategy_name, time_spent);
}