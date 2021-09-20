#include "timer.h"

TimeRecord create_time_recorder()
{
    // create a shared time recorder using mmap
    TimeRecord time_recorder =
        (TimeRecord) mmap( 
                NULL,
                sizeof(TimeRecord),
                PROT_READ  | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                0, 
                0
            );

    return time_recorder;
}

void record_solution_time(int strategy_mode) 
{
    // stop solution time for the solution
    clock_t end_solution_time = clock();

    double time_spent = 
        (double) (end_solution_time - time_recorder->start_time) / (double) (CLOCKS_PER_SEC);

    if (strategy_mode == THREADS_STRATEGY)
    {
        time_recorder->thread_times[time_recorder->time_counter++] = time_spent;
    }
    else
    {
        time_recorder->fork_times[time_recorder->time_counter++] = time_spent;
    }
}

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
    time_recorder->start_time = clock();

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

            // int pid = fork();

            // if (pid == 0) // children
            // {
                solve_with_forks(
                    DEFAULT_START_DIRECTION, 
                    0, 
                    0, 
                    0, 
                    0, 
                    0,
                    WAIT
                );
            // }
            // else if (pid > 0) // parent
            // {
            //     wait(NULL);
            // }
    
        break;

        default:
            printf("Unknown strategy mode");
    }

    // reset for solution indexing
    time_recorder->solutions_amount = time_recorder->time_counter;
    time_recorder->time_counter = 0;

    // finish taking the time
    clock_t end = clock();
}

void show_solution_times() 
{
    for (int i = 0; i < time_recorder->solutions_amount; i++)
    {
        printf(
            "\nSolution %d\nTHREADS: %lf secs\nFORKS: %lf secs\n\n", 
            i+1,
            time_recorder->thread_times[i],
            time_recorder->fork_times[i]
        );
    }
}