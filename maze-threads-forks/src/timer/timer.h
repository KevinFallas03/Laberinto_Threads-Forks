#ifndef CLOCK_PER_SEC
    #include <time.h>
#endif

#define DEFAULT_START_DIRECTION 's' // DOWN

TimeRecord create_time_recorder();
void eval_solver(char *filename,int strategy_mode);
void show_solution_times();
void record_solution_time(int strategy_mode);

