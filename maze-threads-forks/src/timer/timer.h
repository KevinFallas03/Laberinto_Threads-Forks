#ifndef CLOCK_PER_SEC
    #include <time.h>
#endif

#define DEFAULT_START_DIRECTION 's' // DOWN

void eval_solver(
    void (*solve)(char,int,int,int,int,int), 
    char *strategy_name, 
    char *filename);

