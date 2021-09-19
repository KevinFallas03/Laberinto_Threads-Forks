#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h>
#include <pthread.h>

#include "memo/memo.c"
#include "loader/loader.c"

Maze original_maze = NULL;

#include "solver/solver.c"
#include "timer/timer.c"

void run_threads_and_fork_solvers(char *filename);
void test_write_file();

unsigned long xd() {
    return 0L;
}

pthread_t f() {

}



int main(int argc, char const *argv[])
{
    char *filename = "../files/lab1.txt";
    run_threads_and_fork_solvers(filename);

    return EXIT_SUCCESS;
}



void run_threads_and_fork_solvers(char *filename) {
    
    clean_directory();
    srand(time(NULL));

    //eval_solver(solve_with_threads, "THREADS", filename, THREADS_MODE);
    eval_solver(filename, THREADS_MODE);

    //show_results();
}

void manual_test() 
{
    original_maze->map[0][0] = 1;
    print_maze(original_maze);
    original_maze->map[1][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][1] = 2;
    print_maze(original_maze);
    original_maze->map[2][2] = 2;
    print_maze(original_maze);
    original_maze->map[1][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][3] = 4;
    print_maze(original_maze);
    original_maze->map[0][4] = 4;
    print_maze(original_maze); 
}

// void test_write_file() 
// {
//     char *filename = "../xd.txt";
//     char *content = "Hola mundo desde C";

//     write_file(filename, content);

//     char *file_content = NULL;
//     file_content = read_file(filename);
//     printf("%sasdasd\n", file_content);
// }

