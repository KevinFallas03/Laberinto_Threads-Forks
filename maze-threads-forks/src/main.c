#include <string.h>

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
    char file_path[60] = "../files/maps/";
    char filename[25];

    printf("%s","Ingrese el nombre del archivo: ");

    scanf("%s", filename);

    strcat(file_path, filename);

    run_threads_and_fork_solvers( file_path );

    return EXIT_SUCCESS;
}