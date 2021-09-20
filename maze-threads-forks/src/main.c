#include <string.h>

#include "memo/memo.c"
#include "loader/loader.c"

TimeRecord time_recorder = NULL;
Maze original_maze = NULL;

#include "solver/solver.c"
#include "timer/timer.c"

// command line interface utils
void read_file_path(char file_path[]);

#define INPUT_BUFFER_SIZE 60

void assemble() 
{   
    // clean old solutions files     
    clean_directory();

    // set random seed using clock time
    srand(time(NULL));

    // initialize the time recorder with shared memory
    time_recorder = create_time_recorder();
}

void disassemble() 
{   
    exit(0);
}

void run_threads_and_fork_solvers() {

    assemble();

    // request file name of the maze
    char file_path[INPUT_BUFFER_SIZE] = "../files/maps/";
    read_file_path(file_path);

    // solve with forks strategy
    eval_solver(file_path, FORKS_MODE);

    // wait until user wants to continue solving with threads strategy
    printf("\n\nRun threads mode ...PRESS ENTER...\n\n");
    while ( getchar() != '\n' );

    // solve with threads strategy
    eval_solver(file_path, THREADS_MODE);
    
    // show times for solutions with both strategies
    show_solution_times();

    // save solutions files
    // show_results();

    disassemble();
}

int main(int argc, char const *argv[])
{
    run_threads_and_fork_solvers();

    return EXIT_SUCCESS;
}

void read_file_path(char file_path[]) 
{
    char filename[INPUT_BUFFER_SIZE / 2];
    printf("%s","Ingrese el nombre del archivo: ");
    scanf("%s", filename);
    strcat(file_path, filename);
    while(getchar() != '\n');
}