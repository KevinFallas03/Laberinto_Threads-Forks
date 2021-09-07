#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "maze-solver/solver.c"


int main() {
    srand(time(NULL));
    
    create_thread('s',0,0,0);
    return 0;
}

