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

    // allocate memory for timeval pointer
    time_recorder->start_time =
        (struct timeval *) mmap( 
                NULL,
                sizeof(struct timeval),
                PROT_READ  | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                0, 
                0
            ); 

    time_recorder->end_time =
        (struct timeval *) mmap( 
                NULL,
                sizeof(struct timeval),
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
    struct timeval t_end, t_res;
    
    gettimeofday(&t_end, NULL);

    // substract end time with start time using timeval
    timersub(&t_end, time_recorder->start_time, &t_res);

    if (strategy_mode == THREADS_STRATEGY)
    {
        time_recorder->thread_times[time_recorder->time_counter] = t_res.tv_sec;
        time_recorder->thread_times_u[time_recorder->time_counter] = t_res.tv_usec;
    }
    else
    {
        time_recorder->fork_times[time_recorder->time_counter] = t_res.tv_sec;
        time_recorder->fork_times_u[time_recorder->time_counter] = t_res.tv_usec;
    }
    
    time_recorder->time_counter++;
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
    gettimeofday(time_recorder->start_time, NULL);

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

    // reset for solution indexing
    time_recorder->solutions_amount = time_recorder->time_counter;
    time_recorder->time_counter = 0;
}

void show_solution_times() 
{
    for (int i = 0; i < time_recorder->solutions_amount; i++)
    {
        printf(
            "\nSolution %d\nTHREADS: %ld.%06ld secs\nFORKS: %ld.%06ld secs\n\n", 
            i+1,
            (long int) time_recorder->thread_times[i],
            (long int) time_recorder->thread_times_u[i],

            (long int) time_recorder->fork_times[i],
            (long int) time_recorder->fork_times_u[i]
        );
    }
}