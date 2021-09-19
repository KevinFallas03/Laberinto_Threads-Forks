#ifndef CLOCK_PER_SEC
    #include <time.h>
#endif

#define DEFAULT_START_DIRECTION 's' // DOWN

#define THREADS_STRATEGY 0
#define FORKS_STRATEGY   1

void eval_solver(
    char *filename,
    int strategy_mode
);

