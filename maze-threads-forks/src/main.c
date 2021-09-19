#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h>
#include <pthread.h>

#include "memo/memo.c"
#include "loader/loader.c"

Maze original_maze = NULL;

#include "solver/solver.c"
#include "timer/timer.c"

void assemble() 
{        
    clean_directory();
    srand(time(NULL));
}

void disassemble() 
{
    
    exit(0);
}

void run_threads_and_fork_solvers(char *filename) {

    assemble();

    eval_solver(filename, FORKS_MODE);

    printf("\n\nRun threads mode ...PRESS ENTER...\n\n");
    while ( getchar() != '\n' );

    eval_solver(filename, THREADS_MODE);

    // show_results();

    disassemble();
}

int main(int argc, char const *argv[])
{
    char *filename =    
        "../files/lab2.txt";
    
    run_threads_and_fork_solvers( filename );

    return EXIT_SUCCESS;
}