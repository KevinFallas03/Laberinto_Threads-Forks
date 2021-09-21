#ifndef size_t
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define __MEMO__

#define TIME_BUFFER_SIZE 20

typedef struct maze {
    int width;
    int height;
    char **map;
}* Maze;

typedef struct dimension {
    int width;
    int height;
}* Dimension;

typedef struct timer_record {
    struct timeval *start_time;
    struct timeval *end_time;

    time_t fork_times[TIME_BUFFER_SIZE];
    time_t thread_times[TIME_BUFFER_SIZE];
    time_t fork_times_u[TIME_BUFFER_SIZE];
    time_t thread_times_u[TIME_BUFFER_SIZE];

    int time_counter;
    int solutions_amount;
}* TimeRecord;

#define THREADS_STRATEGY 0
#define FORKS_STRATEGY   1

#include <sys/mman.h>

Maze create_shared_maze(Dimension dim);
Maze create_maze(Dimension dim);