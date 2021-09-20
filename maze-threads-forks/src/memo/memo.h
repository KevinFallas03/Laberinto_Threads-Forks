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
    clock_t start_time;
    clock_t end_time;
    double fork_times[TIME_BUFFER_SIZE];
    double thread_times[TIME_BUFFER_SIZE];
    int time_counter;
    int solutions_amount;
}* TimeRecord;

#define THREADS_STRATEGY 0
#define FORKS_STRATEGY   1

#include <sys/mman.h>

Maze create_shared_maze(Dimension dim);
Maze create_maze(Dimension dim);